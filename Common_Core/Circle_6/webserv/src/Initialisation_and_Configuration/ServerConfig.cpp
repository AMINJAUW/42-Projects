#include "ServerConfig.hpp"

ServerConfig::ServerConfig(void):
env(NULL), host(0), port(80)
{
	this->name.clear();
	this->error_page.clear();
	this->routes.clear();
}

ServerConfig::ServerConfig(string const &buffer, const Env *p_env):
env(p_env), host(0), port(80)
{
	size_t	start;
	size_t	end;

	this->name.clear();
	this->error_page.clear();
	this->routes.clear();
	start = buffer.find_first_not_of(SPACE_CHARS, 6);
	if (buffer.compare(0, 6, "server") != 0 || buffer[start] != '{')
		throw (LocationConfig::ParsingException(
			"Unrecognized token between context name and context definition"));
	start = buffer.find_first_not_of(SPACE_CHARS, start + 1);
	while (buffer[start] != '}')
	{		
		if (buffer.compare(start, 8, "location") == 0)
			end = find_closing_bracket(buffer, start) + 1;
		else
			end = buffer.find(';', start);
		this->add_parameter(buffer.substr(start, end - start));
		start = buffer.find_first_not_of(" \t\n\v\f\r;", end + 1);
	}
	this->initiate_defaut_values();
}

ServerConfig::ServerConfig(ServerConfig const &ref):
LocationConfig(static_cast<LocationConfig const &>(ref)), env(ref.env)
{
	*this = ref;
}

ServerConfig &ServerConfig::operator=(ServerConfig const &ref)
{
	this->host = ref.host;
	this->port = ref.port;
	this->name = ref.name;
	this->error_page = ref.error_page;
	this->routes = ref.routes;
	this->listening_socket = ref.listening_socket;
	this->sockaddr = ref.sockaddr;
	this->exchange_socket = ref.exchange_socket;
	this->directives = ref.directives;
	return (*this);
}

ServerConfig::~ServerConfig(void)
{
	;
}

void	ServerConfig::add_parameter(string param)
{
	size_t	end_name = param.find_first_of(SPACE_CHARS);
	string	key = param.substr(0, end_name);
	size_t	start_values = param.find_first_not_of(SPACE_CHARS, end_name);
	string	values;

	if (start_values != string::npos)
		values = param.substr(start_values, param.size() - start_values);
	if (key != "location" && param.find('\n') != string::npos)
		throw (LocationConfig::ParsingException("New line in token \"" + param + "\""));
	while (std::isspace(values[values.size() - 1]))
		values.erase(values.size() - 1);
	if (key == "cgi_path")
		this->process_path(key, values);
	else if (key == "error_page")
		this->process_error_page(values);
	else if (key == "listen")
		this->process_listen(values);
	else if (key == "location")
		this->process_location(param);
	else if (key == "server_name")
		this->process_name(values);
	else
		LocationConfig::add_parameter(param);	
}

void	ServerConfig::process_error_page(string values)
{
	std::vector<int>	error_pages;
	size_t				start = 0;
	size_t				end = values.find_first_of(SPACE_CHARS, 0);
	string				str = values.substr(start, end - start);

	if (str.size() != 3 || str.find_first_of("0123456789") == string::npos)
		throw (LocationConfig::ParsingException("Unknown code in \"error_page\" parameter"));
	while (str.size() == 3 && str.find_first_of("0123456789") != string::npos)
	{
		error_pages.push_back(std::atoi(str.c_str()));
		if (end == string::npos)
			throw (LocationConfig::ParsingException("No page in \"error_page\" parameter"));
		start = values.find_first_not_of(SPACE_CHARS, end + 1);
		end = values.find_first_of(SPACE_CHARS, start);
		str = values.substr(start, end - start);
	}	
	if (end != string::npos)
		throw (LocationConfig::ParsingException("Too much parameters in \"error_page\" parameter"));
	for (size_t i = 0; i < error_pages.size(); i++)
		this->error_page[error_pages[i]] = str;
}

void	ServerConfig::process_listen(string values)
{
	size_t	start = 0;
	size_t	end = values.find_first_of(SPACE_CHARS, 0);

	if (values == "" || start == string::npos || end != string::npos)
		throw (LocationConfig::ParsingException(
			"Wrong number of values in \"listen\" parameter: " + values));
	else
	{
		if (values.find_first_not_of("0123456789") == string::npos)
			this->port = std::atoi(values.c_str());
		else
			this->load_host_port(values.c_str());
	}
	this->directives["listen"] = values;
	if (port > IPV6PORT_ANONMAX)
		throw (LocationConfig::ParsingException(
			"Port too high in \"listen\" parameter: " + values));
}

void	ServerConfig::process_location(string param)
{
	string			target;
	size_t			start = 0;
	size_t			end = 0;
	LocationConfig	ref(param);

	start = param.find_first_not_of(SPACE_CHARS, param.find_first_of(SPACE_CHARS, 0));
	end = param.find_first_of(SPACE_CHARS, start);
	while (param[start] != '{')
	{
		target = param.substr(start, end - start);
		if (target.empty())
			throw (LocationConfig::ParsingException ("Location given without a route"));
		if (target[0] != '/')
			target = '/' + target;
		while (target[target.size() - 1] == '/' && target.size() > 1)
			target.erase(target.size() - 1);
		this->routes[target] = (ref);
		start = param.find_first_not_of(SPACE_CHARS, param.find_first_of(SPACE_CHARS, end));
		end = param.find_first_of(SPACE_CHARS, start);
	}
}

void	ServerConfig::process_name(string values)
{
	size_t	start = 0;
	size_t	end = values.find_first_of(SPACE_CHARS, 0);
	
	if (values == "" || start == string::npos || end != string::npos)
		throw (LocationConfig::ParsingException(
			"Wrong number of values in \"name\" parameter: " + values));
	else
		this->name = values.substr(start, end - start);
}

void	ServerConfig::load_host_port(string s)
{
	size_t	start = 0;
	size_t	end = s.find_first_not_of("0123456789");
	for (unsigned int i = 0; i < 4; i++)
	{
		if (end - start > 3 || (end - start == 3 && s.compare(start, 3, "255") > 0)
			|| (i != 3 && s[end] != '.') || end >= s.size() - 1 
			|| (i == 3 && s[end] != ':'))
			throw (LocationConfig::ParsingException("Wrong host format in \"listen\" parameter"));
		this->host <<= 8;
		this->host += std::atoi(s.substr(start, start - end).c_str());
		start = end + 1;
		end = s.find_first_not_of("0123456789", start);
	}
	this->port = std::atoi(s.substr(start, end - start).c_str());
}

void	ServerConfig::connection_open(void)
{
	this->listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->listening_socket < 0)
	{
		perror("cannot create socket");
		throw (std::exception());
	}
	set_reuse(this->listening_socket);
	fcntl(this->listening_socket, F_SETFL, O_NONBLOCK);
	bzero(&this->sockaddr, sizeof(sockaddr));
	this->sockaddr.sin_family = AF_INET;
	this->sockaddr.sin_port = htons(this->port);
	this->sockaddr.sin_addr.s_addr = htonl(this->host);
	if (bind(this->listening_socket, (struct sockaddr *)&this->sockaddr, sizeof(this->sockaddr)) < 0)
	{
		perror("bind failed");
		throw (std::exception());
	}
	if (listen(this->listening_socket, SOMAXCONN) < 0)
	{
		perror("listen failed");
		throw (std::exception());
	}
	Server::pfd_add(this->listening_socket, POLLIN, NULL, LISTENING_SOCKET);
}

void	ServerConfig::connection_accept(std::vector<ServerConfig> server_configs)
{
	socklen_t	length;
	Server		*ex;

	length = sizeof(this->sockaddr);
	this->exchange_socket = accept(this->listening_socket,
								(struct sockaddr *)&this->sockaddr,
								&length);
	if (this->exchange_socket < 0) 
	{
		perror("accept failed");
		return;
	}
	if (fcntl(this->exchange_socket, F_SETFL, O_NONBLOCK) < 0) 
	{
		close(this->exchange_socket);
		perror("Unable to set fd to NONBLOCKING");
		return;
	}
	ex = new Server(server_configs, *this->env);
	Server::pfd_add(this->exchange_socket, POLLIN | POLLOUT, ex, EXCHANGE_SOCKET);
}

std::ostream	&operator<<(std::ostream &o, const ServerConfig &s)
{
	o << "------------------------------\n------------SERVER------------\n------------------------------\n";
	o << "name: " << s.name << "\n";
	o << "host: " << s.host << "\n";
	o << "port: " << s.port << "\n";
	o << "---------ERROR PAGES----------\n";
	for (std::map<int, string>::const_iterator it = s.error_page.begin();
		it != s.error_page.end(); it++)
		o << it->first << ": " << it->second << "\n";
	o << "-------DEFAULT headers--------\n";
	if (s.directives.empty())
	{
		o << "No directives for the ServerConfig !\n";
		return o;
	}
	for (std::map<string, string>::const_iterator it = s.directives.begin(); it != s.directives.end(); ++it)
	{
		o << it->first << ": " << it->second << "\n";
	}
	o << "-----------ROUTES-------------\n";
	for (std::map<string, LocationConfig>::const_iterator it = s.routes.begin();
		it != s.routes.end(); it++)
	{
		o << it->first << ": \n";
		o << it->second << "\n";
	}
	return (o);
}

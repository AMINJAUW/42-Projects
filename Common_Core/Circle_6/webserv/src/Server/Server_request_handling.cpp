#include "Server.hpp"

void	Server::fill_env(void)
{
	this->env.add_one("SERVER_METHOD", this->request.method);
	this->env.add_one("QUERY_STRING", this->request.query_string);
	for (std::map<string, string>::const_iterator it = request.headers.begin();
		it != request.headers.end(); ++it)
		this->env.add_one("HTTP_" + uppercase(it->first), it->second);
}

void Server::find_server_config(void)
{
	string	host = request.headers.at("Host");

	for (size_t i = 0; i < this->server_configs.size(); i++)
	{
		if (this->server_configs[i].name == host)
		{
			this->server_config = (&this->server_configs[i]);
			return ;
		}
	}
	this->server_config = &this->server_configs[0];
}

void Server::find_location_config(void)
{
	std::map<string, LocationConfig>::iterator	it;
	std::map<string, LocationConfig>::iterator	ite = this->server_config->routes.end();

	this->location_config = this->server_config;
	this->location = "/";
	for (it = this->server_config->routes.begin(); it != ite; it++)
	{
		if (this->request.url.find(it->first) == 0 
			&& it->first.size() > this->location.size())
			this->location = it->first;
	}
	if (this->server_config->routes.find(this->location) != ite)
		this->location_config = &this->server_config->routes[this->location];
}

/* Returns a positive int in case of request's body being larger than parameter
"client_max_body_size". In any other case, returns 0. */
int	Server::check_body_size(void)
{
	long	size;

	if (this->location_config->directives.find("client_max_body_size") 
		== this->location_config->directives.end())
		return (0);
	size = std::atol(
		this->location_config->directives["client_max_body_size"].c_str());
	if (size > 0 && this->request.body.size() > static_cast<size_t>(size))
	{
		this->error_response(413);
		return (-1);
	}
	return (0);
}

void	Server::open_cgi(void)
{
	if (this->cgi.cgi_open() == -1)
	{
		this->error_response(502);
		return ;
	}
	this->env.add_one("PATH_INFO", this->final_url);
	Server::pfd_add(this->cgi.forward[0], POLLIN, this, CGI_FORWARD_OUT);
	Server::pfd_add(this->cgi.forward[1], POLLOUT, this, CGI_FORWARD_IN);
	Server::pfd_add(this->cgi.backward[0], POLLIN, this, CGI_BACKWARD_OUT);
	this->state = WRITING_CGI;
}


void	Server::update_server_attributes(void)
{
	this->update_url();
	if (this->update_url_type() == -1)
		return;
	else if (this->url_type == CGI) 
		this->open_cgi();
}

bool 	Server::is_redirection(void) 
{
	return (location_config->directives.find("return") != location_config->directives.end()
		&& this->valid_Method() != INVALID_METHOD);
}

/* Reads from a fd into the server buffer. */
bool Server::read_to_buffer(int fd)
{
	char	buf[BUFFER_SIZE + 1] = {0};
	int		valread = read(fd, buf, BUFFER_SIZE);

	if (valread == -1)
	{
		this->error_response(500);
		return (false);
	}
	if (valread == 0)
		return (true);
	this->buffer += buf;
	bzero(buf, BUFFER_SIZE);
	return (valread < BUFFER_SIZE);
}

string	Server::uppercase(string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (std::isalnum(str[i]))
			str[i] = std::toupper(str[i]);
		else
			str[i] = '_';
	}
	return (str);
}

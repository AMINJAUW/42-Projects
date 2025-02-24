#include "Server.hpp"

pollfd					*Server::pfds = NULL;
std::map<int, FD_TYPE>	Server::pfds_types;
std::map<int, Server*>	Server::pfds_servers;
std::deque<int>			Server::to_remove;

Server::Server(void)
{
	return ;
}

Server::Server(std::vector<ServerConfig> server_configs, Env p_env):
server_configs(server_configs), server_config(NULL), env(p_env), state(READING_INPUT), 
url_type(OTHER), protocol("HTTP/1.1"), status(0), message("")
{
	this->buffer.clear();
	return ;
}

Server::Server(Server const &ref)
{
	*this = ref;
	return ;
}

Server &Server::operator=(Server const &ref)
{
	this->server_configs = ref.server_configs;
	this->server_config = ref.server_config;
	this->location_config = ref.location_config;
	this->location = ref.location;
	this->env = ref.env;
	this->request = ref.request;
	this->final_url = ref.final_url;
	this->state = ref.state;
	this->url_type = ref.url_type;
	this->cgi = ref.cgi;
	this->cgi_pid = ref.cgi_pid;
	this->cgi_start = ref.cgi_start;
	this->cgi_return_code = ref.cgi_return_code;
	this->upload_fd = ref.upload_fd;
	this->upload_existing_file = ref.upload_existing_file;
	this->buffer = ref.buffer;
	this->protocol = ref.protocol;
	this->status = ref.status;
	this->message = ref.message;
	this->headers = ref.headers;
	this->body = ref.body;
	return (*this);
}

Server::~Server(void)
{
	return ;
}

void	Server::write_redirection_response(void)
{
	this->state = WRITING_OUTPUT;
	this->status = std::atoi(this->location_config->directives.at("return").substr(0, 3).c_str());
	this->headers["Location"] = "http://" 
		+ this->server_config->directives.at("listen") 
		+ this->location_config->directives.at("return").substr(4, string::npos);
}

string	Server::to_string(void)
{
	string								response;
	std::map<string, string>::iterator	it;
	std::map<string, string>::iterator	ite = this->headers.end();

	response = this->protocol + " " 
			+ number_to_string(this->status) + " " 
			+ this->message + "\n";
	for (it = this->headers.begin(); it != ite; it++)
	{
		response += it->first;
		if (it->second.empty() == false)
			response += ": " + it->second;
		response += "\r\n";
	}
	response += "\n";
	response += this->body;
	return (response);
}

#include "Server.hpp"

void	Server::cgi_write(int fd)
{
	int	valwrite;

	if (this->request.method == "POST") 
	{
		valwrite = write(fd, this->request.body.c_str(), this->request.body.size());
		if (valwrite == -1)
		{
			this->cgi.cgi_close();
			this->error_response(500);
			return ;
		}
		if (valwrite == 0)
			cerr << "CGI launched on a POST request with no data\n";
	}
	close(fd);
	Server::to_remove.push_back(fd);
	this->state = LAUNCHING_CGI;
	this->buffer.clear();
}

void	Server::cgi_launch(int fd)
{
	gettimeofday(&this->cgi_start, NULL);
	Server::to_remove.push_back(fd);
	this->state = READING_CGI;
	string exec = this->location_config->directives["cgi"].substr(
		this->location_config->directives["cgi"].rfind(" ") + 1, string::npos);
	if (*(--this->server_config->directives["cgi_path"].end()) != '/'
		&& exec[0] != '/')
		exec = '/' + exec;
	exec = this->server_config->directives["cgi_path"] + exec;
	if (this->cgi.cgi_run(exec.c_str(),	this->final_url.c_str(),
		this->env.get_envp(), &this->cgi_pid) == -1)
		this->cgi_interrupt(502);
}

void	Server::cgi_read(int fd)
{
	if (read_to_buffer(fd) == true || this->state != READING_CGI)
	{
		if (this->state == READING_CGI)
			this->state = BUILDING_RESPONSE;
		close(this->cgi.forward[0]);
		close(this->cgi.backward[0]);
		close(this->cgi.backward[1]);
		Server::to_remove.push_back(cgi.forward[0]);
		Server::to_remove.push_back(cgi.backward[0]);
	}
}

void	Server::cgi_interrupt(int code)
{
	if (code == 504)
		kill(this->cgi_pid, SIGQUIT);
	this->error_response(code);
	close(this->cgi.forward[0]);
	close(this->cgi.backward[0]);
	close(this->cgi.backward[1]);
	Server::to_remove.push_back(cgi.forward[0]);
	Server::to_remove.push_back(cgi.backward[0]);
}

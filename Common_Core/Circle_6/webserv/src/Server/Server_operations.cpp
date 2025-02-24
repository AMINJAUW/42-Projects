#include "Server.hpp"

void	Server::choose_operation(Cluster &cluster, const int &i)
{
	pollfd	&pfd = Server::pfds[i];
	FD_TYPE	type = Server::pfds_types[pfd.fd];
	Server	&server = *Server::pfds_servers[pfd.fd];

	server.handle_errors(type);
	if (pfd.revents & POLLIN && type == LISTENING_SOCKET)
		cluster[i][0].connection_accept(cluster[i]);
	else if (pfd.revents & POLLIN && type == EXCHANGE_SOCKET && server.state == READING_INPUT)
		server.build_request(pfd.fd);
	else if (pfd.revents & POLLOUT && type == CGI_FORWARD_IN && server.state == WRITING_CGI)
		server.cgi_write(pfd.fd);
	else if (pfd.revents & POLLIN && type == CGI_FORWARD_OUT && server.state == LAUNCHING_CGI)
		server.cgi_launch(pfd.fd);
	else if ((pfd.revents & POLLIN) && type == CGI_BACKWARD_OUT && server.state == READING_CGI)
		server.cgi_read(pfd.fd);
	else if (pfd.revents & POLLOUT && type == EXCHANGE_SOCKET && server.state == BUILDING_RESPONSE)
		server.build_response();
	else if (pfd.revents & POLLIN && type == TARGET && server.state == READING_TARGET)
		server.target_read(pfd.fd);
	else if (pfd.revents & POLLOUT && type == UPLOAD_TARGET && server.state == UPLOADING_DATA)
		server.data_upload(pfd.fd);
	else if (pfd.revents & POLLOUT && type == EXCHANGE_SOCKET && server.state == WRITING_OUTPUT)
		server.respond(pfd.fd);
}

void	Server::handle_errors(FD_TYPE type)
{
	if (type == CGI_BACKWARD_OUT && this->state == READING_CGI)
	{
		if (time_interval_sec(this->cgi_start) >= TIMEOUT_LIMIT)
			this->cgi_interrupt(504);
		else if (waitpid(this->cgi_pid, NULL, WNOHANG) != 0)
			this->cgi_interrupt(502);
	}
}

void	Server::build_request(int fd)
{
	if (this->read_to_buffer(fd) == false)
		return ;
	this->state = BUILDING_RESPONSE;
	try
	{
		this->request = Request(this->buffer);
	}
	catch (Request::BadRequest &e)
	{
		if (this->request.headers.find("Host") != this->request.headers.end())
			this->find_server_config();
		else
			this->server_config = &server_configs[0];
		this->error_response(e.code);
		return;
	}
	this->fill_env();
	this->find_server_config();
	this->find_location_config();
	if (this->check_body_size() == -1)
		return ;
	if (this->is_redirection() == true)
	{
		this->write_redirection_response();
		return ;
	}
	this->update_server_attributes();
}

void	Server::build_response(void)
{
	this->state = WRITING_OUTPUT;
	if (this->url_type == CGI)
	{
		if (this->store_cgi_response() == -1 || this->complete_cgi_header() == -1)
			this->error_response(500, "CGI format error");
		return ;
	}
	this->apply_method();
}

void	Server::target_read(int fd)
{
	
	if (read_to_buffer(fd) == true)
	{
		this->body = this->buffer;
		this->headers["Content-Length"] = number_to_string(this->body.size());
		close(fd);
		Server::to_remove.push_back(fd);
		this->state = WRITING_OUTPUT;
	}
}

void	Server::data_upload(int fd)
{
	int	valwrite;

	valwrite = write(fd, this->request.body.c_str(), this->request.body.size());
	if (valwrite == -1)
	{
		this->error_response(500);
		return ;
	}
	else if (valwrite == 0)
	{
		this->status = 200;
		this->body = "Empty body, no data uploaded\n";
	}
	else if (this->status == 0 && this->upload_existing_file == 0)
	{
		this->status = 200;
		this->body = "File successfully appended";
	}
	else if (this->status == 0)
	{
		this->status = 201;
		this->body = "File successfully uploaded";
	}
	this->message = default_message(this->status);
	this->headers["Location"] = this->location + 
		this->location_config->directives["upload_store"] + this->request.url;
	this->headers["Content-Length"] = number_to_string(this->body.size());
	this->headers["Content-Type"] = "text/plain";
	close(fd);
	Server::to_remove.push_back(fd);
	this->state = WRITING_OUTPUT;
}

void	Server::respond(int fd)
{
	int		valwrite;
	string	response = this->to_string();

	valwrite = write(fd, response.c_str(), response.size());
	if (valwrite == -1)
		cerr << "Response write failure, closing connection\n";
	else if (valwrite == 0)
		cerr << "Empty reply sent\n";
	close(fd);
	Server::to_remove.push_back(fd);
}

#include "Server.hpp"
 
/* Generates a message corresponding to error_code unless there is already some
message in this->message. */
void	Server::error_response(int error_code)
{
	if (this->message.empty() == true)
		this->error_response(error_code, default_message(error_code));
	else
		this->error_response(error_code, this->message);
}

/* Overwrites this->message with "message". */
void	Server::error_response(int error_code, string const message)
{
	this->state = WRITING_OUTPUT;
	this->status = error_code;

	if (message.empty())
	{
		this->error_response(error_code);
		return;
	}
	this->message = message;

	if (this->server_config->error_page.find(error_code) 
		== this->server_config->error_page.end())
		this->generate_error(error_code, message);
	else
	{
		this->final_url = this->server_config->error_page.find(error_code)->second;
		if (access(this->final_url.c_str(), F_OK) == -1)
			generate_error(404, "default error page not found");
		else if (access(this->final_url.c_str(), R_OK) == -1)
			generate_error(403, "permission denied for default error page");
		else
		{
			this->headers["Content-Type"] = this->getContentType(this->final_url);
			int fd = open(this->final_url.c_str(), O_RDONLY | O_NONBLOCK);
			Server::pfd_add(fd, POLLIN, this, TARGET);
			this->buffer.clear();
			this->state = READING_TARGET;
		}
	}
}

void	Server::generate_error(int error_code, string const message)
{
	std::stringstream	error_page;

	error_page << "<!DOCTYPE html>\n"
			   << "<html>\n"
			   << "<head>\n"
			   << "    <title>Error " << error_code << "</title>\n"
			   << "</head>\n"
			   << "<body>\n"
			   << "    <h1>Error " << error_code << "</h1>\n"
			   << "    <p>" << message << "</p>\n"
			   << "</body>\n"
			   << "</html>\n";
	this->body = error_page.str();
	this->headers["Content-Type"] = "text/html";
	this->headers["Content-Length"] = number_to_string(this->body.size());
}

# include "Server.hpp"

void Server::apply_method(void)
{
	switch (this->valid_Method())
	{
		case GET:
			this->GET_response();
			break;

		case POST:
			this->POST_response();
			break;

		case DELETE:
			this->DELETE_response();
			break;

		default:
			this->error_response(405);
			break;
	}
	return ;
}

/* Note : if a file name ends with a trailing slash it should give 404 and not
a folder error. */
void	Server::GET_response(void)
{
	if (this->url_type == FOLDER)
	{
		this->generate_autoindex();
		return ;
	}
	else if (this->url_type == FILE_NOT_FOUND)
	{
		this->error_response(404, "File not found");
		return ;
	}
	else if (this->url_type == PERMISSION_DENIED)
	{
		this->error_response(403, "Forbidden");
		return ;
	}
	this->status = 200;
	this->message = "OK";

	string file_name = this->final_url.substr(this->final_url.find_last_of('/') + 1);
	this->headers["Content-Type"] = this->getContentType(file_name);

	int fd = open(this->final_url.c_str(), O_RDONLY | O_NONBLOCK);
	Server::pfd_add(fd, POLLIN, this, TARGET);
	this->buffer.clear();
	this->state = READING_TARGET;
}

void	Server::POST_response(void)
{
	if (this->url_type != UPLOAD)
		this->GET_response();
	else
	{
		string	path = this->location_config->directives["root"]
			+ this->location_config->directives["upload_store"] + this->request.url;
		string	directory = strip_file(path);
		if (mkdir_p(directory) != 0)
		{
			this->error_response(500, "Internal Server Error");
			return;
		}
		this->upload_existing_file = access(path.c_str(), F_OK);
		this->upload_fd = open(path.c_str(), O_CREAT | O_RDWR | O_APPEND | O_NONBLOCK, 0644);
		Server::pfd_add(upload_fd, POLLOUT, this, UPLOAD_TARGET);
		this->state = UPLOADING_DATA;
	}
}

void		Server::DELETE_response(void)
{
	if (this->url_type == FILE_NOT_FOUND)
	{
		this->error_response(404, "File not found");
		return ;
	}
	if (remove(this->final_url.c_str()) == -1)
	{
		if (errno == EACCES) 
			this->error_response(403);
		else
			this->error_response(500);
		return;
	}
	this->status = 200;
	this->message = "OK";
	this->body = "";
	this->headers["Content-Length"] = number_to_string(this->body.size());
	this->headers["Content-Type"] = "text/plain";
}

METHOD		Server::valid_Method(void) const
{
	string	available_limit_except;

	if (location_config->directives.find("limit_except") != location_config->directives.end())
		available_limit_except = location_config->directives.at("limit_except");
	else
		available_limit_except = this->server_config->directives.at("limit_except");

	std::istringstream	iss(available_limit_except);
	string				method;
	while (iss >> method)
	{
		if (this->request.method == method)
		{
			if (method == "GET")
				return (GET);
			else if (method == "POST")
				return (POST);
			else
				return (DELETE);
		}
	}
	return (INVALID_METHOD);
}

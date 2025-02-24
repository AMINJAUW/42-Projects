#include "Server.hpp"

void	Server::update_url(void)
{
	string root = this->location_config->directives["root"];

	if (this->location != "/")
		this->request.url.erase(0, this->location.size());
	this->final_url = this->request.url;
	if (root != "/")
		this->final_url = root + this->final_url;
	this->final_url = remove_trailing(this->final_url, "/");
}

/* Returns -1 if there is an error and calls the right error_response(). */
int	Server::update_url_type(void)
{
	this->url_type = find_url_type(this->final_url);

	if (this->url_type == FOLDER)
	{
		int status = 404;
		string	default_page = this->valid_default_file(status);
		if (default_page == "")
		{
			if (this->request.method == "DELETE")
			{
				this->error_response(403, "DELETE asked on a Directory Forbbiden");
				return (-1);
			}
			else if (this->location_config->directives.find("autoindex") == this->location_config->directives.end() 
				|| this->location_config->directives.at("autoindex") == "off")
			{
				this->error_response(404);
				return (-1);
			}
			else
				this->url_type = FOLDER;
		}
		else
		{
			this->final_url = default_page;
			this->url_type = this->find_url_type(this->final_url);
		}
	}
	return (1);
}

URL_TYPE	Server::find_url_type(string &url)
{
	if (this->request.method != "DELETE" 
		&& this->location_config->directives.find("cgi") 
			!= this->location_config->directives.end()
		&& valid_cgi(this->location_config->directives["cgi"], url) == true)
		return (CGI);
	else if (this->request.method == "POST" 
		&& this->location_config->directives.find("upload_store") 
			!= this->location_config->directives.end()
			&& (access(url.c_str(), F_OK) != 0 || access(url.c_str(), W_OK) == 0))
		return (UPLOAD);
	DIR *temp = opendir(url.c_str());
	if (temp != NULL)
	{
		closedir(temp);
		return (FOLDER);
	}
	else if (access(url.c_str(), F_OK) != 0)
		return (FILE_NOT_FOUND);
	else if (access(url.c_str(), R_OK) != 0)
		return (PERMISSION_DENIED);
	else
		return (OTHER);
}

string	Server::valid_default_file(int &status_code)
{
	if (this->location_config->directives.find("index") 
		== this->location_config->directives.end())
		return "";

	std::istringstream	iss(this->location_config->directives["index"]);
	string				default_page;
	while (iss >> default_page)
	{
		if (default_page[0] != '/')
			default_page = "/" + default_page;

		if (this->final_url != "/") 
			default_page = this->final_url + default_page;

		if (access(default_page.c_str(), F_OK) == -1)
		{
			if (status_code != 403)
				status_code = 404;
			continue;
		}
		DIR * dir = opendir(default_page.c_str());
		if (dir != NULL)
		{
			status_code = 403;
			closedir(dir);
			continue;
		}
		if (access(default_page.c_str(), R_OK) == -1)
		{
			status_code = 403;
			continue;
		}
		return default_page;
	}
	return "";
}

#include "Server.hpp"

void	Server::generate_autoindex(void)
{
	DIR 				*dir = opendir(this->final_url.c_str());
	std::stringstream	body;

	body << "<html><head><title>Directory Listing</title></head><body><h1>Directory Listing</h1><ul>";
	for(struct dirent* entry = readdir(dir); entry != NULL; entry = readdir(dir))
	{
		if (string(entry->d_name) == ".")
			continue ;
		if (string(entry->d_name) == ".." && this->final_url == location_config->directives.at("root"))
			continue;
		string full_path = this->final_url + "/" + entry->d_name;
		full_path = this->remove_from_path_closest_root(full_path);

		body << "<li><a href=\"" << full_path << "\">" << entry->d_name << "</a></li>";
	}
	body << "</ul></body></html>";
	closedir(dir);
	this->body = body.str();
	this->status = 200;
	this->message = "Autoindex";
	this->headers["Content-Type"] = "text/html";
	this->headers["Content-Length"] = number_to_string(this->body.size());
}

string	Server::remove_from_path_closest_root(string full_path) const
{
	if (this->location_config->directives.at("root") != "/")
		full_path = full_path.substr(this->location_config->directives.at("root").size(), string::npos);
	if (this->server_config->routes.find("/") != this->server_config->routes.end() && !(this->server_config->routes.at("/") == *(this->location_config)))
		full_path = key_in_map_for_value<string, LocationConfig>(this->server_config->routes, *(this->location_config)) + full_path;
	return full_path;
}

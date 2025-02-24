#include "ServerConfig.hpp"

void ServerConfig::initiate_defaut_values()
{
	if (this->directives.find("root") == this->directives.end())
		this->directives["root"] = "/";
	if (this->directives.find("limit_except") == this->directives.end())
		this->directives["limit_except"] = "GET POST DELETE";
	if (this->directives.find("autoindex") == this->directives.end())
		this->directives["autoindex"] = "off";
	if (this->directives.find("listen") == this->directives.end())
	{
		this->directives["listen"] = "0.0.0.0:80";
		this->load_host_port("0.0.0.0:80");
	}
	
	std::vector<string> paths = vector_of_keys<string, LocationConfig>(this->routes);
	if (paths.size() > 1)
		std::sort(paths.begin(), paths.end(), ServerConfig::DepthComparator(*this));
	for (size_t i = 0; i < paths.size(); i++)
	{
		string closest_parent = this->closest_parent_location(paths, i);
		LocationConfig *parent_location;
		if (closest_parent == "")
			parent_location = this;
		else
			parent_location = &(this->routes.at(closest_parent));
		this->copy_default_values(parent_location, &(this->routes.at(paths[i])));	
	}
}

void	ServerConfig::copy_default_values(LocationConfig const *src, LocationConfig *dest)
{
	std::vector<string> attributes = vector_of_keys<string, string>(src->directives);

	for (size_t i = 0; i < attributes.size(); i++)
	{
		if (dest->directives.find(attributes[i]) == dest->directives.end())
			dest->directives[attributes[i]] = src->directives.at(attributes[i]);
	}
}

string	ServerConfig::closest_parent_location(std::vector<string> const paths, size_t pos) const
{
	for (int i = pos - 1; i >= 0; --i)
	{
		if (paths[i].find(paths[pos]) == 0)
			return (paths[i]);
	}
	return ("");
}

bool ServerConfig::depth_cmp(string const &s1, string const &s2) const
{
	return (this->folder_depth(s1) < this->folder_depth(s2));
}

int	ServerConfig::folder_depth(string const path) const
{
	int	counter = 0;
	if (path == "/")
		return 0;
	for (size_t i = 0; path[i]; ++i)
	{
		if (path[i] == '/')
			counter++;
	}
	return (counter);	
}

#include "Server.hpp"

int	Server::store_cgi_first_line(std::vector<string> &lines)
{
	int	status_read;

	if (lines[0].find_first_of("HTTP/1.1") == 0 && sscanf(lines[0].c_str(), "HTTP/1.1 %d", &status_read) == 1)
	{
		if (status_read < 100 || status_read >= 600)
			return (-1);
		this->protocol = lines[0].substr(0, 8);
		this->status = status_read;
		if (lines[0].size() < 14)
			return (-1);
		this->message = lines[0].substr(13, string::npos);
		lines.erase(lines.begin());
	}
	return (1);
}

int	Server::store_cgi_headers(std::vector<string> &lines)
{
	size_t	i = 0;

	while (i < lines.size() && lines[i].compare("") != 0 && lines[i].compare("\r") != 0)
	{
		size_t key_end = lines[i].find(':');
		string key = lines[i].substr(0, key_end);
		if (key_end == string::npos)
			return (-1);

		size_t value_start = lines[i].find_first_not_of(' ', key_end + 1);
		if (value_start == string::npos)
			return (-1);

		size_t value_end = lines[i].size();
		string value = lines[i].substr(value_start, value_end);

		this->headers[key] = value;
		if (key == "Status")
			this->status = std::atoi(value.c_str());
		i++;
	}
	lines.erase(lines.begin(), lines.begin() + i);
	if (lines.size() != 0)
		lines.erase(lines.begin());
	return (1);
}

int	Server::store_cgi_response(void) 
{
	std::vector<string>	lines;

	get_lines(this->buffer, lines);
	if (store_cgi_first_line(lines) == -1)
		return (-1);
	if (store_cgi_headers(lines) < 0)
		return (-1);
	for(size_t i = 0; i < lines.size(); i++)
		this->body += lines[i] + "\n";
	return (0);
}

int Server::complete_cgi_header(void)
{
	if (this->status == 0)
		this->status = 200;
	if (this->message.empty() == true)
		this->message = default_message(this->status);
	if (this->headers.find("Content-Type") == this->headers.end())
		this->headers["Content-Type"] = "text/html";
	if (this->headers.find("Content-Length") == this->headers.end())
		this->headers["Content-Length"] = number_to_string(this->body.size());
	return (1);
}

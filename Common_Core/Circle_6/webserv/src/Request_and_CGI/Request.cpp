#include "Request.hpp"

Request::Request(void)
{
	return ;
}

/* Constructs an instance of Request based on a string received from the 
client. The first line is parsed as method-url-protocol line. The ones between
the second line and a potential empty line are parsed as headers. The ones
following a potential empty line are parsed as body. An error is thrown if
'buffer' is empty or if no "Host" header has been found after the headers
parsing. */
Request::Request(const string &buffer):
body("")
{
	std::vector<string>	lines;
	std::stringstream	ss(buffer);
	size_t				i = 1;

	if (buffer.empty() == true)
		throw(BadRequest());

	string	line;
	while(std::getline(ss, line, '\n'))
		lines.push_back(line);
	this->parse_first_line(remove_trailing(lines[0], "\r"));
	while (lines[i].compare("\r") != 0)
	{
		this->parse_header(lines[i]);
		i++;
	}
	if (this->headers.find("Host") == this->headers.end())
		throw BadRequest();

	i++;
	if (this->headers.find("Content-Length") != this->headers.end())
		this->check_content_length(std::vector<string>(lines.begin() + i, lines.end()));

	this->parse_body(std::vector<string>(lines.begin() + i, lines.end()));
	this->parse_query_string();
}

Request::Request(Request const &ref)
{
	*this = ref;
	return ;
}

Request &Request::operator=(Request const &ref)
{
	this->method = ref.method;
	this->url = ref.url;
	this->protocol = ref.protocol;
	this->headers = ref.headers;
	this->body = ref.body;
	this->query_string = ref.query_string;
	return (*this);
}

Request::~Request(void)
{
	return ;
}

/* Assigns what's before the first space of 'line' to string 'method', what's
between the first and the second space to string 'url', and what's after the
second space to string 'protocol'. Throws an error if no word has been
encounterd where one should have, if the url doesn't start with '/', if
there are still characters after the last word, if the protocol isn't HTTP/1.1
or if the uri exceeds MAX_URI_SIZE. */
void	Request::parse_first_line(const string &line)
{
	size_t	start = 0;
	size_t	end = line.find(' ', start);
	string	word;

	for (int i = 0; i < 3; i++)
	{
		word = line.substr(start, end - start);
		if (start == string::npos || std::isspace(word[0]) == true
			|| (i == 1 && word[0] != '/')
			|| (i == 2 && word != "HTTP/1.1")
			|| (i == 2 && line.find_first_not_of(" ", end) != string::npos))
			throw (BadRequest());
		else if (i == 1 && word.size() > MAX_URI_SIZE)
			throw (BadRequest(414));
		else if (i == 0)
			this->method = word;
		else if (i == 1)
			this->url = word;
		else if (i == 2)
			this->protocol = word;
		start = end + 1;
		end = line.find(' ', start);
	}
}
/* Checks if the Content-Length is a valid value and if so if it is not smaller than the body received
Else throw BadRequest*/
void	Request::check_content_length(std::vector<string> lines)
{
	int len = std::atoi(this->headers["Content-Length"].c_str());
	if (this->headers["Content-Length"] != number_to_string(len))
		throw BadRequest();
	
	int body_size = 0;
	for(size_t i = 0; i < lines.size(); ++i)
	{
		body_size += lines[i].size();
	}
	if (len < body_size)
	{
		throw BadRequest();
	}
}

void	Request::check_host(string host)
{
	if (this->headers.find("Host") != this->headers.end())
		throw BadRequest();
	
	if (host == "")
		throw BadRequest();

	string invalid_chars = "~/?#[]@!$&'()*+,;=";

	for (size_t i = 0; i < invalid_chars.size(); i++)
	{
		if (host.find(invalid_chars[i]) != string::npos)
			throw BadRequest();
	}
}

/* Creates a new pair of key-value in headers map, assigning the first word of
'line' to its key and the rest to its value. Throws an error if the key is
"Host" and a header with this key already exists in the request headers. 
If the key isn't Hostand is already registered, the function adds the values to
the ones already existing at this key. */
void	Request::parse_header(const string &line)
{
	size_t	key_size = line.find_first_of(':');
	if (key_size == string::npos || key_size == 0 || key_size > line.find_first_of(' '))
		throw Request::BadRequest();
	size_t	value_start = line.find_first_not_of(' ', key_size + 1);
	string	key = format_header_key(line.substr(0, key_size));
	string	value;


	if (value_start == string::npos)
		value = "";
	else
		value = remove_trailing(line.substr(value_start, string::npos), SPACE_CHARS);

	if (key == "Host")
		this->check_host(value);
	
	if (key == "Content-Length" && this->headers.find("Content-Length") != this->headers.end())
		throw BadRequest();

	this->headers[key] += value;
}

/* Unchunks the lines if needed and appends every string of lines to 'body'. */
void	Request::parse_body(std::vector<string> lines)
{
	if (this->is_chunked(lines) == false)
	{
		if (this->headers.find("Transfer-Encoding") != this->headers.end()
			&& this->headers.at("Transfer-Encoding") == "chunked")
			throw BadRequest();
		for (size_t i = 0; i < lines.size(); ++i)
			this->body += lines[i];
	}
}

/* Replaces the placeholders (%xx) with the right chararacters and associate
the environment variable. */
void	Request::parse_query_string()
{
	size_t	separator_index = this->url.find_first_of('?');
	string	full_url = this->url;

	this->url = full_url.substr(0, separator_index);
	this->query_string = full_url.substr(separator_index + 1, string::npos);
	if (url_decoding(this->query_string) == -1 || url_decoding(this->url) == -1)
		throw BadRequest();
}

Request::BadRequest::BadRequest(void):code(400) {}

Request::BadRequest::BadRequest(const int p_code):code(p_code) {}

Request::BadRequest::~BadRequest(void) throw() {}

std::ostream	&operator<<(std::ostream &o, const Request &s)
{
	o << "------------------------------\n"
		<< "------------REQUEST-----------\n"
		<< "------------------------------\n";
	o << "METHOD: " << s.method << "\n";
	o << "url: " << s.url << "\n";
	o << "PROTOCOL: " << s.protocol << "\n";
	for (std::map<string, string>::const_iterator it = s.headers.begin();
		it != s.headers.end(); it++)
		o << it->first << ": " << it->second << "\n";
	o << "BODY:\n" << s.body;	
	return (o);
}

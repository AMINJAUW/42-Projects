#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# pragma once

# include <cctype>
# include <iostream>
# include <fcntl.h>
# include <fstream>
# include <sstream>
# include <map>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <vector>

# define BUFFER_SIZE 50000
# define MAX_URI_SIZE 6000
# define TIMEOUT_LIMIT 10
# define SPACE_CHARS " \t\n\v\f\r"

# define RESET_COLOR "\x1B[0m"
# define RED "\x1B[1;31m"
# define YELLOW "\x1B[1;33m"
# define GREEN "\x1B[1;32m"

using std::string;
using std::endl;
using std::cout;
using std::cerr;

enum FD_TYPE {
	LISTENING_SOCKET,
	EXCHANGE_SOCKET,
	CGI_FORWARD_IN,
	CGI_FORWARD_OUT,
	CGI_BACKWARD_OUT,
	TARGET,
	UPLOAD_TARGET
};

enum SERVER_STATE {
	LISTENING,
	READING_INPUT,
	WRITING_CGI,
	LAUNCHING_CGI,
	READING_CGI,
	BUILDING_RESPONSE,
	READING_TARGET,
	UPLOADING_DATA,
	WRITING_OUTPUT
};

enum URL_TYPE {
	FILE_NOT_FOUND,
	PERMISSION_DENIED,
	OTHER,
	CGI,
	FOLDER,
	UPLOAD
};

enum METHOD {
	INVALID_METHOD,
	GET,
	POST,
	DELETE
};

string			check_file(int argc, char **argv);
string			load_file(const string file);
void			get_lines(string buffer, std::vector<string> &lines);
string			strip_file(string path);
int 			mkdir_p(string const &fullpath);

size_t			find_closing_bracket(const string &string, size_t start);
int				url_decoding(string &url);
string			remove_trailing(string str, const string &set);
string			format_header_key(string key);

void			set_reuse(int sfd);
long long int	time_interval_sec(timeval comp);
bool			valid_cgi(string const &cgi_pass, string const &url);

string 			default_message(int code);

template <typename T>
string number_to_string (T Number)
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

template <typename T, typename U>
T key_in_map_for_value(std::map<T,U> const map, U const value)
{
	for (typename std::map<T,U>::const_iterator it = map.begin(); it != map.end(); ++it)
	{
		if (it->second == value)
			return it->first;
	}
	return T();
}

template <typename T, typename U>
std::vector<T> vector_of_keys(std::map<T, U> map)
{
	typename std::vector<T> keys;
	for(typename std::map<T,U>::const_iterator it = map.begin(); it != map.end(); ++it)
	{
		keys.push_back(it->first);
	}
	return keys;
}

#endif

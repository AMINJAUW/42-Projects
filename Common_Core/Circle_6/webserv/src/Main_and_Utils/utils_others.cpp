#include "webserv.hpp"

long long int	time_interval_sec(timeval comp)
{
	timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec - comp.tv_sec - (comp.tv_usec > time.tv_usec));
}

void	set_reuse(int socket_fd)
{
	int	enable = 1;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) 
	{
		perror("setsockopt(SO_REUSEADDR) failed");
		throw(std::exception());
	}
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) < 0) 
	{
		perror("setsockopt(SO_REUSEPORT) failed");
		throw(std::exception());
	}
}

bool	valid_cgi(string const &cgi, string const &url)
{
	string	ext = cgi.substr(0, cgi.find_first_of(" ", 0));
	if (url.rfind(ext) != url.size() - ext.size())
		return (false);
	return (true);
}

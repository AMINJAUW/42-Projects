#ifndef CGI_HANLDER_HPP
# define CGI_HANLDER_HPP

# pragma once

# include "webserv.hpp"
# include <fcntl.h>
# include <string>
# include <unistd.h>

class Server;

class CGI_handler
{
	public:
		CGI_handler(void);
		CGI_handler(CGI_handler const &ref);
		CGI_handler &operator=(CGI_handler const &ref);
		~CGI_handler(void);
		int		cgi_open(void);
		int		cgi_run(const char *exec, const char *target, char **envp, int *pid);
		void	cgi_close(void);
		int		forward[2];
		int		backward[2];

	private:
};

# include "Server.hpp"

#endif

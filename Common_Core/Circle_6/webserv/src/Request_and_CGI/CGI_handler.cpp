#include "CGI_handler.hpp"

CGI_handler::CGI_handler(void)
{
	return ;
}

CGI_handler::CGI_handler(CGI_handler const &ref)
{
	*this = ref;
	return ;
}


CGI_handler &CGI_handler::operator=(CGI_handler const &ref)
{
	this->forward[0] = ref.forward[0];
	this->forward[1] = ref.forward[1];
	this->backward[0] = ref.backward[0];
	this->backward[1] = ref.backward[1];
	return (*this);
}

CGI_handler::~CGI_handler(void)
{
	return ;
}

int	CGI_handler::cgi_open(void)
{
	if (pipe(this->forward) != 0)
		return (-1);
	if (pipe(this->backward) != 0)
	{
		close(this->forward[0]);
		close(this->forward[1]);
		return (-1);
	}
	fcntl(this->forward[0], F_SETFL, O_NONBLOCK);
	fcntl(this->forward[1], F_SETFL, O_NONBLOCK);
	fcntl(this->backward[0], F_SETFL, O_NONBLOCK);
	fcntl(this->backward[1], F_SETFL, O_NONBLOCK);
	return (0);
}

int	CGI_handler::cgi_run(const char *exec, const char *target, char **envp, int *pid)
{
	char	**args = new char *[3];
	args[0] = static_cast<char *>(calloc(strlen(exec) + 1, sizeof(char)));
	strlcpy(args[0], exec, strlen(exec) + 1);
	args[1] = static_cast<char *>(calloc(strlen(target) + 1, sizeof(char)));
	strlcpy(args[1], target, strlen(target) + 1);
	args[2] = NULL;

	*pid = fork();
	if (*pid == -1)
	{
		this->cgi_close();
		return (-1);
	}
	if (*pid == 0)
	{
		dup2(this->forward[0], STDIN_FILENO);
		dup2(this->backward[1], STDOUT_FILENO);
		this->cgi_close();
		for (unsigned int it = 0; it < Server::pfds_servers.size(); it++)
			close(Server::pfds[it].fd);
		execve(exec, args, envp);
		exit(1);
	}
	free(args[0]);
	free(args[1]);
	delete [] args;
	return (0);
}

void CGI_handler::cgi_close(void)
{
	close(this->forward[0]);
	close(this->forward[1]);
	close(this->backward[0]);
	close(this->backward[1]);
}

#include "Server.hpp"

/* Adds a pollfd structure to Server::pfds, the array of pollfd monitoring the
readiness of the various fds. At the same time, add the type of the
corresponding fd to Server::pfds_types and the associate server to
Server::pfds_server. If an fd with the same number is still monitored, deletes
it before adding the new one. */
void	Server::pfd_add(int p_fd, int p_flags, Server *p_ex, FD_TYPE p_type)
{
	unsigned int	length;

	if (Server::pfds_servers.find(p_fd) != Server::pfds_servers.end())
		Server::pfd_remove(p_fd);
	length = Server::pfds_servers.size();
	pollfd 	*n_pfds = new pollfd[length + 1];
	for (unsigned int i = 0; i < length; i++)
		n_pfds[i] = Server::pfds[i];
	n_pfds[length].fd = p_fd;
	n_pfds[length].events = p_flags;
	n_pfds[length].revents = 0;
	delete[] Server::pfds;
	Server::pfds = n_pfds;
	Server::pfds_types[p_fd] = p_type;
	Server::pfds_servers[p_fd] = p_ex;
}

/* Deletes a pollfd structure from Server::pfds, the array of pollfd monitoring
the readiness of the various fds. At the same time, deletes the type of the
corresponding fd from Server::pfds_types and the associate server from
Server::pfds_server. If the fd correspond to an exchange socket, it delete the
server object. If the fd with this number isn't monitored, the function has no
effect. */
void	Server::pfd_remove(int p_fd)
{
	unsigned int	length;
	unsigned int	i_original;

	if (Server::pfds_servers.find(p_fd) == Server::pfds_servers.end())
		return ;
	length = Server::pfds_servers.size();
	i_original = 0;
	pollfd	*n_pfds = new pollfd[length - 1];
	for (unsigned int i = 0; i < length - 1; i++)
	{
		if (Server::pfds[i_original].fd == p_fd)
			i_original++;
		n_pfds[i] = Server::pfds[i_original];
		i_original++;
	}
	delete[] Server::pfds;
	Server::pfds = n_pfds;
	if (Server::pfds_types[p_fd] == EXCHANGE_SOCKET)
		delete Server::pfds_servers[p_fd];
	Server::pfds_types.erase(p_fd);
	Server::pfds_servers.erase(p_fd);
}

void	Server::pfds_clean(void)
{
	while (Server::to_remove.empty() == false)
	{
		Server::pfd_remove(Server::to_remove[0]);
		Server::to_remove.pop_front();
	}
}

void	Server::close_all_requests(void)
{
	std::map<int, FD_TYPE>::iterator it = --Server::pfds_types.end();

	while (it->second != LISTENING_SOCKET)
	{
		if (it->second == CGI_BACKWARD_OUT)
			kill(Server::pfds_servers[it->first]->cgi_pid, 9);
		close(it->first);
		Server::pfd_remove(it->first);
		it = --Server::pfds_types.end();
	}
}

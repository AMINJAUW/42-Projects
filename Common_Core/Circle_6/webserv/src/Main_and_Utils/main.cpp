#include "Cluster.hpp"
#include "Request.hpp"
#include "ServerConfig.hpp"
#include "webserv.hpp"
#include <poll.h>

int main (int argc, char **argv, char **envp)
{
	const string	file(check_file(argc, argv));
	const Env		env(envp);
	Cluster			cluster;
	size_t			size;

	if (BUFFER_SIZE < 1 || MAX_URI_SIZE < 1 || TIMEOUT_LIMIT < 1)
	{
		cerr << "Wrong macro value: check inc/webserv.hpp\n";
		return (1);
	}
	try
	{
		cluster.fill(file, &env);
		for (size_t i = 0; i < cluster.size(); ++i) 
			cluster[i][0].connection_open();
	}
	catch(const std::exception &e)
	{
		return (1);
	}

	while (1)
	{
		size = Server::pfds_types.size();
		if (poll(Server::pfds, size, -1) == -1)
		{
			perror("In poll");
			Server::close_all_requests();
			continue ;
		}
		for (size_t i = 0; i < size; ++i)
			Server::choose_operation(cluster, i);
		Server::pfds_clean();
	}
}

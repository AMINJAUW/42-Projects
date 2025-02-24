#ifndef CLUSTER_HPP
# define CLUSTER_HPP

# pragma once
# include "ServerConfig.hpp"
# include "webserv.hpp"
# include <vector>

class Cluster : public std::vector< std::vector< ServerConfig > >
{
	public:
		Cluster(void);
		Cluster &operator=(Cluster const &ref);
		~Cluster(void);
		void	fill(const string &file, const Env *env);

	private:
		Cluster(Cluster const &ref);
		void	push_server_config(const ServerConfig &s);
		int		find_host_port(const string &host_port);
};

std::ostream	&operator<<(std::ostream &o, Cluster const &c);

#endif

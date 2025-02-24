#ifndef SERVERCONFIG_HPP
# define SERVERCONFIG_HPP

# pragma once
# include "LocationConfig.hpp"
# include "webserv.hpp"
# include <algorithm>
# include <fcntl.h>
# include <iostream>
# include <map>
# include <netinet/in.h>
# include <sys/socket.h>
# include <unistd.h>

class Env;
class Server;

class ServerConfig : public LocationConfig
{
	public:
		ServerConfig(void);
		ServerConfig &operator=(ServerConfig const &ref);
		ServerConfig(string const &buffer, const Env *p_env);
		ServerConfig(ServerConfig const &ref);
		~ServerConfig(void);
		const Env							*env;
		unsigned int						host;
		unsigned int						port;
		string								name;
		std::map<int, string>				error_page;
		std::map<string, LocationConfig>	routes;
		int									listening_socket;
		sockaddr_in							sockaddr;
		int									exchange_socket;
		void	connection_open(void);
		void	connection_accept(std::vector<ServerConfig> server_configs);

	private:
		void	add_parameter(string param);
		void	process_error_page(string values);
		void	process_listen(string values);
		void	process_location(string param);
		void	process_name(string values);
		void	load_host_port(string s);

		void	initiate_defaut_values();
		int		folder_depth(string const path) const;
		bool 	depth_cmp(string const &s1, string const &s2) const;
		string	closest_parent_location(std::vector<string> const paths, size_t pos) const;
		void	copy_default_values(LocationConfig const *src, LocationConfig *dest);

		/*
		DepthComparator is a functor :O
		It's made because std::sort takes a comparator function that just takes 2 things to compare.
		And because our function to compare take implicitly also "this" we need to make a functor 
		{N.B. in c++11 there is a thing called Lambda functions that can acheive the same thing}
		*/
		class DepthComparator { 
			public :
				DepthComparator(const ServerConfig& server) : server(server) {}

				bool operator()(const string& s1, const string& s2) const {
					return this->server.depth_cmp(s1, s2);
				}
			private :
				const ServerConfig &server;
		};
};

std::ostream	&operator<<(std::ostream &o, const ServerConfig &s);

# include "Server.hpp"

#endif

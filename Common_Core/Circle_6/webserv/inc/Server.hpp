#ifndef SERVER_HPP
# define SERVER_HPP

# pragma once
# include "CGI_handler.hpp"
# include "Env.hpp"
# include "Request.hpp"
# include "ServerConfig.hpp"
# include "webserv.hpp"
# include <unistd.h>
# include <deque>
# include <dirent.h>
# include <iostream>
# include <map>
# include <poll.h>
# include <signal.h>
# include <string>
# include <strings.h>
# include <sys/time.h>
# include <sys/types.h>

class Cluster;

class Server
{
	public:
		Server(std::vector<ServerConfig> server_configs, Env p_env);
		Server(Server const &ref);
		~Server(void);
		Server 								&operator=(Server const &ref);
		string								to_string(void);

		static pollfd					*pfds;
		static std::map<int, FD_TYPE>	pfds_types;
		static std::map<int, Server*>	pfds_servers;
		static std::deque<int>			to_remove;

		std::vector<ServerConfig>		server_configs;
		ServerConfig					*server_config;
		LocationConfig					*location_config;
		string							location;
		Env								env;
		Request							request;
		string							final_url;

		SERVER_STATE					state;
		URL_TYPE						url_type;
		CGI_handler						cgi;
		int								cgi_pid;
		timeval							cgi_start;
		int								cgi_return_code;
		int								upload_fd;
		int								upload_existing_file;
		string							buffer;

		string							protocol;
		int								status;
		string							message;
		std::map<string, string>		headers;
		string							body;

		/* FD MONITORING */
		static void		choose_operation(Cluster &cluster, const int &i);
		static void		close_all_requests(void);
		static void		pfd_add(int p_fd, int p_flags, Server *p_ex, FD_TYPE p_type);
		static void		pfd_remove(int p_fd);
		static void		pfds_clean(void);

		/* REQUEST CONSTRUCTION */
		void			build_request(int fd);
		void			fill_env(void);
		void 			find_server_config(void);
		void			find_location_config(void);
		int				check_body_size(void);
		void			update_server_attributes(void);
		void			update_url(void);
		int				update_url_type(void);
		URL_TYPE		find_url_type(string &url);
		string			valid_default_file(int &status_code);
		void			open_cgi(void);
	
		/* CGI MANAGEMENT */
		void				cgi_write(int fd);
		void				cgi_launch(int fd);
		void				cgi_read(int fd);
		int					store_cgi_response(void);
		int					store_cgi_first_line(std::vector<string> &lines);
		int 				store_cgi_headers(std::vector<string> &lines);
		int					complete_cgi_header(void);

		/* RESPONSE CONSTRUCTION */
		bool			is_redirection(void);
		void			write_redirection_response(void);
		void			build_response(void);
		void			apply_method(void);
		METHOD			valid_Method(void) const;
		void 			GET_response(void);
		void 			POST_response(void);
		void 			DELETE_response(void);
		void			generate_autoindex(void);
		void			target_read(int fd);
		void			data_upload(int fd);
		void			respond(int p_fd);

		/* ERROR MANAGEMENT */
		void			handle_errors(FD_TYPE type);
		void			cgi_interrupt(int code);
		void			error_response(int error_code);
		void			error_response(int error_code, string const message);
		void			generate_error(int error_code, string const message);

		/* OTHERS */
		bool			read_to_buffer(int fd);
		inline string	uppercase(string str);
		string			remove_from_path_closest_root(string full_path) const;
		string 			getContentType(const string& filename) const;

	private:
		Server(void);
};

# include "Cluster.hpp"

#endif

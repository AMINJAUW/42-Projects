#ifndef LOCATION_HPP
# define LOCATION_HPP

# pragma once
# include "webserv.hpp"
# include <cctype>
# include <iostream>
# include <map>
# include <set>
# include <sstream>

class LocationConfig
{
	public:
		LocationConfig(void);
		LocationConfig(string const &str);
		LocationConfig(LocationConfig const &ref);
		LocationConfig	&operator=(LocationConfig const &ref);
		bool		operator==(LocationConfig const &ref) const;
		~LocationConfig(void);
		std::map<string, string>	directives;
		class ParsingException: public std::exception{
			public:
				ParsingException(const string p_s);
				~ParsingException(void) throw();
				const string	str;
		};

	protected:
		void	process_autoindex(string values);
		void	process_cgi(string values);
		void	process_client_max_body_size(string values);
		void	process_limit_except(string values);
		void	process_return(string values);
		void	process_path(string key, string values);
		void	add_parameter(string param);
	
	private:
};

std::ostream	&operator<<(std::ostream &o, const LocationConfig &l);

#endif

#ifndef REQUEST_HPP
# define REQUEST_HPP

# pragma once

# include "Env.hpp"
# include "webserv.hpp"
# include <cstdio>
# include <iostream>
# include <map>
# include <string>
# include <vector>

class Request
{
	public:
		Request(void);
		Request(const string &buffer);
		Request(Request const &ref);
		Request &operator=(Request const &ref);
		~Request(void);
		string						method;
		string						url;
		string						query_string;
		string						protocol;
		std::map<string, string>	headers;
		string						body;
		class BadRequest: public std::exception
		{
			public:
				BadRequest(void);
				BadRequest(const int code);
				~BadRequest(void) throw();
				const int	code;
		};

	private:
		void	parse_first_line(const string &line);
		void	parse_header(const string &line);
		void	parse_body(std::vector<string> lines);
		bool	is_chunked(std::vector<string> lines);
		void	parse_query_string();
		void	check_host(string host);
		void	check_content_length(std::vector<string> lines);

};

std::ostream	&operator<<(std::ostream &o, const Request &r);

#endif

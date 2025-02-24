#ifndef ENV_HPP
# define ENV_HPP

# pragma once
# include "webserv.hpp"
# include <iostream>
# include <map>

class Env : public std::map<string, string>
{
	public:
		Env(void);
		Env(char **envp);
		Env(Env const &ref);
		Env &operator=(Env const &ref);
		~Env(void);
		void							add_one(char *var);
		void							add_one(string const key, string const value);
		void							reinit(void);
		const std::map<string, string>	get_original(void) const;
		char							**get_envp(void);

	private:
		const std::map<string, string>	original;
		char							**envp;
		const std::map<string, string>	set_original(char **envp);
		void							to_envp(void);
		void							clear_envp(void);
};

#endif

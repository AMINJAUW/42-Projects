#include "Env.hpp"

Env::Env(void):
original(), envp(NULL)
{
	return ;
}

Env::Env(char **envp):
original(set_original(envp)), envp(NULL)
{
	this->reinit();
	return ;
}

Env::Env(Env const &ref):
original(ref.get_original()), envp(NULL)
{
	*this = ref;
	return ;
}

Env &Env::operator=(Env const &ref)
{
	this->clear();
	for (Env::const_iterator it = ref.begin(); it != ref.end(); it++)
		(*this)[it->first] = it->second;
	this->to_envp();
	return (*this);
}

Env::~Env(void)
{
	this->clear_envp();
	return ;
}

void	Env::add_one(char *var)
{
	string	variable(var);
	size_t	separator = variable.find('=');
	string	key = variable.substr(0, separator);
	string	value = variable.substr(separator + 1, variable.size() - (separator + 1));

	(*this)[key] = value;
	return ;
}

void	Env::add_one(string const key, string const value)
{
	(*this)[key] = value;
	return ;
}

void	Env::reinit(void)
{
	this->clear();
	for (Env::const_iterator it = this->original.begin(); it != this->original.end(); it++)
		(*this)[it->first] = it->second;
	return ;
}

const std::map<string, string>	Env::get_original(void) const
{
	return (this->original);
}

char	**Env::get_envp(void)
{
	this->to_envp();
	return (this->envp);
}

const std::map<string, string>	Env::set_original(char **envp)
{
	std::map<string, string> temp;
	if (envp == NULL)
		return (temp);
	for (unsigned int i = 0; envp[i]; i++)
	{
		string variable(envp[i]);
		size_t		separator = variable.find('=');
		string key = variable.substr(0, separator);
		string value = variable.substr(separator + 1, variable.size() - (separator + 1));
		temp[key] = value;
	}
	return (temp);
}

void	Env::to_envp(void)
{
	if (this->envp != NULL)
		this->clear_envp();
	unsigned int	i = 0;
	this->envp = new char *[this->size() + 1];
	for (std::map<string, string>::const_iterator it = this->begin();
		it != this->end(); it++)
	{
		string variable(it->first + "=" + it->second);
		this->envp[i] = new char[variable.size() + 1];
		variable.copy(this->envp[i], variable.size(), 0);
		this->envp[i][variable.size()] = 0;
		i++;
	}
	this->envp[this->size()] = NULL;
}

void	Env::clear_envp(void)
{
	if (envp == NULL)
		return;
	for (unsigned int i = 0; this->envp[i]; i++)
		delete[] this->envp[i];
	delete[] this->envp;
}

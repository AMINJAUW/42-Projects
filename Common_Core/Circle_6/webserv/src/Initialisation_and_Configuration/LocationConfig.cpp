#include "LocationConfig.hpp"

LocationConfig::LocationConfig(void)
{
	;
}

LocationConfig::LocationConfig(string const &s)
{
	size_t	start;
	size_t	end;

	end = s.find('{');
	start = s.find_first_not_of(SPACE_CHARS, end + 1);
	while (start < s.size() - 1)
	{		
		end = s.find(';', start);
		this->add_parameter(s.substr(start, end - start));
		start = s.find_first_not_of(" \t\n\v\f\r;", end + 1);
	}
	if (s[start] != '}')
		throw (LocationConfig::ParsingException("Invalid LocationConfig: " + s));
}

LocationConfig::LocationConfig(LocationConfig const &ref)
{
	*this = ref;
	return ;
}

LocationConfig	&LocationConfig::operator=(LocationConfig const &ref)
{
	this->directives = ref.directives;
	return (*this);
}

bool	LocationConfig::operator==(LocationConfig const &ref) const
{
	if (this->directives.size() != ref.directives.size())
		return (false);
	for (std::map<string, string>::const_iterator it = this->directives.begin();
		it != this->directives.end(); ++it)
	{
		std::map<string, string>::const_iterator ref_it = ref.directives.find(it->first);
		if(ref_it == ref.directives.end() || ref_it->second != it->second)
			return (false);
	}
	return (true);
}

LocationConfig::~LocationConfig(void)
{
	;
}

void	LocationConfig::add_parameter(string param)
{
	size_t	end_name = param.find_first_of(SPACE_CHARS);
	string	key = param.substr(0, end_name);
	size_t	start_values = param.find_first_not_of(SPACE_CHARS, end_name);
	string	values;
	
	if (start_values != string::npos)
		values = param.substr(start_values, param.size() - start_values);
	if (param.find('\n') != string::npos)
		throw (LocationConfig::ParsingException("New line in token \"" + param + "\""));
	while (std::isspace(values[values.size() - 1]))
		values.erase(values.size() - 1);
	if (key == "autoindex")
		this->process_autoindex(values);
	else if (key == "cgi")
		this->process_cgi(values);
	else if (key == "client_max_body_size")
		this->process_client_max_body_size(values);
	else if (key == "return")
		this->process_return(values);
	else if (key == "root" || key == "upload_store")
		this->process_path(key, values);
	else
		this->directives[key] = values;
}

void	LocationConfig::process_autoindex(string values)
{
	if (values != "on" && values != "off")
		throw (LocationConfig::ParsingException(
			"Unknown on/off value in \"autoindex\" parameter: " + values));
	this->directives["autoindex"] = values;
}

void	LocationConfig::process_cgi(string values)
{
	size_t	check = values.find_first_not_of(" ", values.find_first_of(" ", 0));

	if (check == string::npos)
		throw (LocationConfig::ParsingException(
			"Wrong number of values in \"cgi\" parameter: " + values));
	check = values.find_first_not_of(" ", values.find_first_of(" ", check));
	if (check != string::npos)
		throw (LocationConfig::ParsingException(
			"Wrong number of values in \"cgi\" parameter: " + values));
	this->directives["cgi"] = values;
}

void	LocationConfig::process_client_max_body_size(string values) 
{
	if (number_to_string<unsigned int>(std::atoi(values.c_str())) != values)
		throw (LocationConfig::ParsingException(
			"Invalid value in \"client_max_body_size\""));
	this->directives["client_max_body_size"] = values;
}

void	LocationConfig::process_return(string values)
{
	std::istringstream	iss(values);
	string				status_code;

	this->directives["return"] = values;
	iss >> status_code;
	if (status_code.size() != 3 || !std::isdigit(status_code[0]) 
		|| !std::isdigit(status_code[1]) || !std::isdigit(status_code[2])
		|| std::atoi(status_code.c_str()) < 100 
		|| std::atoi(status_code.c_str()) >= 600)
		throw (LocationConfig::ParsingException(
			"Unknown code in \"return\" parameter"));
	size_t pos = values.find(status_code);
	pos += 3;
	while(values[pos] && isspace(values[pos]))
		pos++;
	if (values[pos])
	{
		if (values[pos] != '/')
			throw (LocationConfig::ParsingException(
				"invalid rediection in \"return\" parameter"));
		if (values.find_first_of(SPACE_CHARS, pos) != string::npos)
			throw (LocationConfig::ParsingException(
				"Too much parameters in \"return\" parameter"));
	}
}

void	LocationConfig::process_path(string key, string values)
{
	if (values.find_first_not_of(" ", values.find_first_of(" ", 0)) != string::npos
		|| values == "")
		throw (LocationConfig::ParsingException(
			"Wrong number of values in \"root\" parameter: " + values));
	while (*(--values.end()) == '/')
		values.erase(--values.end());
	this->directives[key] = values;
}

std::ostream	&operator<<(std::ostream &o, const LocationConfig &l)
{
	if (l.directives.empty())
	{
		o << "No directives for the location !\n";
		return o;
	}
	for (std::map<string, string>::const_iterator it = l.directives.begin(); it != l.directives.end(); ++it)
	{
		o << it->first << ": " << it->second << "\n";
	}
	return o;
}

LocationConfig::ParsingException::ParsingException(const string p_s):str(p_s) {}

LocationConfig::ParsingException::~ParsingException(void) throw() {}

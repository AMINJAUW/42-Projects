#include "webserv.hpp"

/* Returns the position in string of the closing bracket corresponding to the
first opening bracket encountered after start. Returns npos if a closing
bracket is found before an opening bracket, or if not enough closing brackets
are found. */
size_t	find_closing_bracket(const string &string, size_t start)
{
	int	open = 1;

	if (string.find('{', start) >= string.find('}', start))
		return (string::npos);
	start = string.find('{', start) + 1;
	while (start < string.size() && open != 0)
	{
		if (string[start] == '{')
			open++;
		else if (string[start] == '}')
			open--;
		start++;
	}
	if (open != 0)
		return (string::npos);
	return (start - 1);
}

int	url_decoding(string &url)
{
	for (size_t index = url.find_first_of("%"); index != string::npos; index = url.find_first_of("%"))
	{
		if (index > url.size() - 3)
			return (-1);
		int char_value;
		if (sscanf(url.substr(index + 1, 2).c_str(), "%x", &char_value) == -1 && sscanf(url.substr(index + 1, 2).c_str(), "%X", &char_value)  == -1)
			return (-1);
		if (char_value < 32 || char_value > 126)
			return (-1);
		url.replace(index, 3, 1, static_cast<char>(char_value));
	}
	return (0);
}

string	remove_trailing(string str, const string &set)
{
	while (str.empty() == false && strchr(set.c_str(), *(--str.end())) != NULL)
		str.erase(--str.end());
	return (str);
}

string	format_header_key(string key)
{
	key[0] = toupper(key[0]);
	for (size_t i = 1; i < key.size(); ++i)
	{
		if (key[i] == '-' && i != key.size() - 1)
		{
			i++;
			key[i] = toupper(key[i]);
		}
		else
			key[i] = tolower(key[i]);
	}
	return key;
}

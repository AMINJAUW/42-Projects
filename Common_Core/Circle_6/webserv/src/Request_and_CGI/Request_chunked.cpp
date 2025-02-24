#include "Request.hpp"

/* Returns the integer translation of an hexadecimal number stored in str.
Returns 0 if the number is invalid. */
static int	hex_number(string str)
{
	int		data_size;
	if (sscanf(str.c_str(), "%x\r", &data_size) == -1 && sscanf(str.c_str(), "%X\r", &data_size) == -1 
		&& sscanf(str.c_str(), "%x;%s\r", &data_size, static_cast<char *>(NULL)) == -1 && sscanf(str.c_str(), "%X;%s\r", &data_size, static_cast<char *>(NULL)) == -1)
		return (-1);
	if (data_size == 0)
	{
		for (size_t i = 0; i < str.size() && str[i] != '\r' && str[i] != ';'; i++)		
		{
			if (str[i] != '0')
				return (-1);
		}	
	}
	return (data_size);
}

static bool	only_trailer(std::vector<string> lines, size_t i)
{
	if (i == lines.size())
		return (false);
	while (i < lines.size())
	{
		if (lines[i].find(":") == string::npos)
			break;
		++i;
	}
	if (i == lines.size() - 1 && lines[i] == "\r")
		return (true);
	else if (i != lines.size())
		return (false);
	return (true);
}


/* Returns a vector of chunks and sizes, and change lines to be only the trailers. */
static std::vector<string>	concatenate_chunked_body(std::vector<string> &lines) 
{
	std::vector<string>	result;
	string				current_chunk;

	for (size_t i = 0; i < lines.size(); i++) 
	{
		if (lines[i].empty())
		{
			current_chunk += '\n';
		}
		else if (lines[i] == "\r")
		{
			result.push_back(current_chunk);
			current_chunk.clear();
		}
		else if (lines[i][lines[i].size() - 1] != '\r')
		{
			current_chunk += lines[i] + "\n";
		}
		else
		{
			current_chunk += lines[i];
			if (hex_number(current_chunk) == 0)
			{
				if (i + 1 < lines.size() && only_trailer(lines, i + 1))
				{
					i++;
					lines.erase(lines.begin(), lines.begin() + i);
					result.push_back(current_chunk);
					return (result);
				}
			}
			result.push_back(current_chunk);
			current_chunk.clear();
		}
	}
	lines.erase(lines.begin(), lines.end());
	if (current_chunk.empty() == false)
		result.push_back(current_chunk);
	return (result);
}

/* If chunked request, unchunks it and fills headers and body with the right values. */
bool	Request::is_chunked(std::vector<string> lines)
{
	string	tmp_body;
	size_t	i = 0;

	if (lines.empty() || (lines.size() == 1 && lines[0] != "0\r"))
		return (false);
	std::vector<string>	chunks = concatenate_chunked_body(lines);
	while (i < chunks.size())
	{
		if (chunks[i].find(":") != string::npos)
			break;
		int size = hex_number(chunks[i]);
		i++;
		if (size == -1)
			return (false);
		else if (size == 0)
			continue;
		else if (i == chunks.size())
			return (false);
		else if (size != static_cast<int>(remove_trailing(chunks[i], "\r").size()))
			return (false);
		tmp_body += remove_trailing(chunks[i], "\r");
		i++;
	}
	for (size_t j = 0; j + 1 < lines.size(); j++)
	{
		this->parse_header(remove_trailing(lines[j], "\r"));
	}
	this->body = tmp_body;
	return (true);
}


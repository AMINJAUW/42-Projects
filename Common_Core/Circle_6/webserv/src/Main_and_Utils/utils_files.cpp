#include "webserv.hpp"

string	check_file(int argc, char **argv)
{
	if (argc == 1)
		return ("conf/default.conf");
	string file(argv[1]);
	if (argc != 2 || file.rfind(".conf") != file.size() - 5)
	{
		cerr << "Usage: ./webserv config_file.conf\n";
		exit(1);
	}
	return (argv[1]);
}

string	load_file(const string file)
{
	std::ifstream	ifs;
	char			temp[BUFFER_SIZE + 1];
	string			buffer;

	ifs.open(file.c_str(), std::ios::in);
	if (ifs.fail() == true)
	{
		perror(file.c_str());
		throw (std::exception());
	}
	while (ifs.eof() == false)
	{
		bzero(temp, BUFFER_SIZE);
		ifs.read(temp, BUFFER_SIZE);
		buffer += temp;
	}
	ifs.close();
	return (buffer);
}

/* Splits buffer on new line characters and stores the split lines in the
vector 'lines'. Keeps the blank lines. 

NOT 100% OK!!!!!!!!!!!!!!!!!!!!! . */
void	get_lines(string buffer, std::vector<string> &lines)
{
	size_t	line_chars = 0;
	string	temp;

	while (buffer.empty() == false)
	{
		line_chars = buffer.find('\n');
		if (line_chars == string::npos)
			line_chars = buffer.size();
		temp = buffer.substr(0, line_chars);
		if (temp.size() > 1 && temp[temp.size() - 1] == '\r')
			temp.erase(temp.size() - 1);
		lines.push_back(temp);
		buffer.erase(0, line_chars + 1);
	}
}

string	strip_file(string path)
{
	if (*--path.end() == '/' && path.size() > 1)
		path.erase(path.size() - 1);
	while (*--path.end() != '/' && path.size() > 1)
		path.erase(path.size() - 1);
	if (path.size() > 1)
		path.erase(path.size() - 1);
	return (path);
}

int	mkdir_p(string const &fullpath)
{
	string	path = "";

	while (path != fullpath)
	{
		path = fullpath.substr(0, fullpath.find('/', path.size() + 1));
		if (access(path.c_str(), F_OK) == -1)
		{	
			if (mkdir(path.c_str(), 0755) == -1)
				return (1);
		}
		else if (access(path.c_str(), R_OK) == -1)
			return (1);
	}
	return (0);
}

#include "Cluster.hpp"

Cluster::Cluster(void)
{
	return ;
}

Cluster::Cluster(Cluster const &ref)
{
	*this = ref;
}

Cluster &Cluster::operator=(Cluster const &ref)
{
	this->clear();
	for (Cluster::const_iterator it = ref.begin(); it != ref.end(); it++)
		this->push_back(*it);
	return (*this);
}

Cluster::~Cluster(void)
{
	for (size_t i = 0; i < this->size(); ++i)
		close((*this)[i][0].listening_socket);
	if (Server::pfds != NULL)
		delete[] Server::pfds;
}

void Cluster::fill(const string &file, const Env *env)
{
	string	buffer;
	size_t	start;
	size_t	end;

	try
	{
		buffer = load_file(file);
		start = buffer.find_first_not_of(SPACE_CHARS, 0);
		while (start != string::npos)
		{
			end = find_closing_bracket(buffer, start) + 1;
			this->push_server_config(
					ServerConfig(buffer.substr(start, end - start), env));
			start = buffer.find_first_not_of(SPACE_CHARS, end);
		}
	}
	catch(const LocationConfig::ParsingException &e)
	{
		cerr << file << ": Parsing exception: " << e.str << "\n";
		throw (std::exception());
	}
	if (this->size() == 0)
	{
		cerr << file << ": No servers defined in file" << "\n";
		throw (std::exception());
	}
}

void	Cluster::push_server_config(const ServerConfig &s)
{
	int	pos;

	pos = this->find_host_port(s.directives.at("listen"));
	if (pos == -1)
	{
		std::vector<ServerConfig> server_vector;
		server_vector.push_back(s);
		this->push_back(server_vector);
	}
	else
		(*this)[pos].push_back(s);
}

int Cluster::find_host_port(const string &host_port)
{
	for (size_t i = 0; i < this->size(); i++)
	{
		if ((*this)[i][0].directives.at("listen") == host_port)
			return (i);
	}
	return (-1);
}

std::ostream	&operator<<(std::ostream &o, Cluster const &c)
{
	for (size_t i = 0; i < c.size(); i++)
	{
		o << "----------------------------------------\n";
		o << "Sub cluster " << i << " of Servers\n";
		o << "----------------------------------------\n\n";
		for (size_t j = 0; j < c[i].size(); j++)
		{
			o << c[i][j];
		}
	}
	return (o);
}

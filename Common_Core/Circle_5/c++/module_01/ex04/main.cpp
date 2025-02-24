/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:55:22 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/17 12:31:51 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <string>
using std::string;


int replace(char **argv, string content)
{
	ofstream	outfile;
	size_t		pos;

	outfile.open(string(argv[1]) + ".replace");
	if (outfile.fail())
	{
		cout << "Error when trying to open " << string(argv[1]) + ".replace" << endl;
		return (1);
	}
	for (size_t i = 0; i < content.size(); i++)
	{
		pos = content.find(argv[2], i);
		while (i < content.size() && (pos == string::npos || i < pos))
		{
			outfile << content[i];
			i++;
		}
		if (pos != string::npos && i < content.size())
		{
			outfile << argv[3];
			i += string(argv[2]).size() - 1;
		}
	}
	return (0);
}

int main (int argc, char **argv)
{
	ifstream	infile;
	string		content;
	char		c;

	if (argc != 4)
	{
		cout << "Wrong number of args" << endl;
		cout << "please use ./sed \"file_pwd\" \"string_to_replace\" \"replacement_string\"" << endl;
		return (1);
	}
	if (argv[1][0] == '\0' || argv[2][0] == '\0' || argv[3][0] == '\0')
	{
		cout << "\nAre you trying to break my sed program ?" << endl;
		cout << "Not very kind of you. But I will not let you go futher sorry\n" << endl;
		return (1);
	}
	infile.open(argv[1]);
	if(infile.fail())
	{
		cout << "Error: " << argv[1] << ":" << \
		" no such file or directory" << endl;
		return (1);
	}
	while (infile.eof() == false && infile >> std::noskipws >> c)
		content += c;
	infile.close();
	return (replace(argv, content));
}
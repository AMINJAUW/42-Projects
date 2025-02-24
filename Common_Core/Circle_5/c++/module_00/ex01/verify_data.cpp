/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_data.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:47:23 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/17 15:53:56 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

bool	valid_phone_nbr(std::string str, int print)
{
	if (str.size() == 0)
		return false;
	std::cout << YELLOW;
	if (str.compare("s") == 0)
	{
		if(print == 1)
			std::cout << "Setting " << "\x1b[38;5;132m" << STD_NBR << YELLOW << " as number" << std::endl;
		if (std::string(STD_NBR).compare("1307") == 0)
		{
			if(print == 1)
				std::cout << LIGHT_GREY << "Default setting for standard number.\n1307 is the Belgium National information for phone numbers." << NO_COLOR << std::endl;
		}
		return true;
	}
	if (str.size() > 9 || str.size() < 7)
	{
		if(print == 1)
			std::cout << "Not a valid phone number or format like 123456789.\nIf you give \'s\' as number it will give the standard number of the company" << NO_COLOR << std::endl;
		return (false);
	}
	for (int i = 1; i < 9; i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if(print == 1)
				std::cout << "Not only numbers in your phone number please try again with a valid phone number like 123456789" << NO_COLOR << std::endl;
			return (false);
		}
	}
	std::cout << NO_COLOR;
	return (true);
}

bool is_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return true;
	if (c >= 'A' && c <= 'Z')
		return true;
	return false;
}

bool	valid_first_name(std::string str, int print)
{
	bool answer = true;

	if (str.size() == 0)
		return false;
	for (size_t i = 0 ;answer && i < str.size(); i++)
	{
		if ((i == 0 || i == str.size() - 1) && (str[i] == ' ' || str[i] == '-'))
			answer = false;
		if (!is_alpha(str[i]) && str[i] != ' ' && str[i] != '-')
			answer = false;
	}
	if (answer == false && print)
		std::cout << RED << "Please put a valid name" << NO_COLOR << std::endl;
	return (answer);
}

bool	valid_last_name(std::string str, int print)
{
	bool answer = true;

	if (str.size() == 0)
		return false;
	for (size_t i = 0 ;answer && i < str.size(); i++)
	{
		if ((i == 0 || i == str.size() - 1) && str[i] == ' ')
			answer = false;
		if (!is_alpha(str[i]) && str[i] != ' ')
			answer = false;
	}
	if (answer == false && print == 1)
		std::cout << RED << "Please put a valid name" << NO_COLOR << std::endl;
	return (answer);
}

std::string *format_first_name(std::string *addr)
{
	std::string	name = *addr;
	for (size_t i = 0; i < name.size(); i++)
	{
		if (i == 0 || name[i - 1] == ' ' || name[i - 1] == '-')
		{
			if (name[i] >= 'a' && name[i] <= 'z')
				name[i] = name[i] - 'a' + 'A';
		}
		else
		{
			if (name[i] >= 'A' && name[i] <= 'Z')
				name[i] = name[i] - 'A' + 'a';
		}
	}
	*addr = name;
	return addr;
}

std::string *format_last_name(std::string *addr)
{
	std::string	name = *addr;
	for (size_t i = 0; i < name.size(); i++)
	{
		if (i == 0 || name[i - 1] == ' ')
		{
			if (name.find(' ', i) == std::string::npos)
			{
				if (name[i] >= 'a' && name[i] <= 'z')
					name[i] = name[i] - 'a' + 'A';
			}
		}
		else if (name[i] >= 'A' && name[i] <= 'Z')
				name[i] = name[i] - 'A' + 'a';
	}
	*addr = name;
	return addr;
}

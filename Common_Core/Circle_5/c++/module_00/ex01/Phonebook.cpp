/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:29:46 by aminjauw          #+#    #+#             */
/*   Updated: 2023/06/21 16:40:41 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

PhoneBook::PhoneBook(void) : _index(0)
{
	std::cout << YELLOW << "Making PhoneBook" << NO_COLOR << std::endl;
	return ;
}

PhoneBook::~PhoneBook(void)
{
	std::cout << RED << "Destroying PhoneBook" << NO_COLOR << std::endl;
	return ;
}

void	PhoneBook::add(void)
{
	std::string	str;
	
	if (this->_index > 7)
	{
		std::cout << BOLD << YELLOW << "Warning maximum contacts achieved... overwriting " 
			<< this->_contacts[this->_index % 8].get_fname() << " "
			<< this->_contacts[this->_index % 8].get_lname() << " contact" 
			<< BOLD_OFF << NO_COLOR << std::endl;
	}
	str = "";
	while (!std::cin.eof() && !valid_first_name(str, 0))
	{
		std::cout << BLUE << "Enter a first name: " << NO_COLOR;
		if (std::getline(std::cin, str) && valid_first_name(str, 1))
			this->_contacts[this->_index % 8].set_fname(*format_first_name(&str));
	}	
	str = "";
	while (!std::cin.eof() && !valid_last_name(str, 0))
	{
		std::cout << BLUE << "Enter " << this->_contacts[this->_index % 8].get_fname()
			<< "\'s last name: " << NO_COLOR;
		if (std::getline(std::cin, str) && valid_last_name(str, 1))
			this->_contacts[this->_index % 8].set_lname(*format_last_name(&str));
	}
	str = "";
	while (!std::cin.eof() && str == "")
	{
		std::cout << BLUE << "Enter " << this->_contacts[this->_index % 8].get_fname()
			<< " " << this->_contacts[this->_index % 8].get_lname() << " nickname: " << NO_COLOR;
		if (std::getline(std::cin, str) && str != "")
			this->_contacts[this->_index % 8].set_nickname(str);
	}
	str = "";
	while (!std::cin.eof() && !valid_phone_nbr(str, 0))
	{
		std::cout << BLUE << "Enter " << this->_contacts[this->_index % 8].get_fname()
			<< " " << this->_contacts[this->_index % 8].get_lname() << "Belgian phone number: +32 " << NO_COLOR;
		if (std::getline(std::cin, str) && valid_phone_nbr(str, 1))
		{
			if (str.compare("s") == 0)
				this->_contacts[this->_index % 8].set_phone_num(std::string(STD_NBR));
			else
				this->_contacts[this->_index % 8].set_phone_num(std::string("+32") + str);
		}
	}
	str = "";
	while (!std::cin.eof() && str == "")
	{
		std::cout << RED << BOLD << "Enter " << this->_contacts[this->_index % 8].get_fname()
			<< " " << this->_contacts[this->_index % 8].get_lname() << " darkest secret: " << "\x1b[95m";
		if (std::getline(std::cin, str) && str != "")
			this->_contacts[this->_index % 8].set_secret(str);
	}
	std::cout << NO_COLOR;
	this->_index++;
	return ;
}

std::string	str_long(std::string str)
{
	if (str.length() < 10)
		return str;
	str.resize(10);
	str[9] = '.';
	return str;
}

void	PhoneBook::search(void) const
{
	int			i;
	std::string	str;
	
	if (this->_index == 0)
	{
		std::cout << RED << "please add contacts before searching" << NO_COLOR <<std::endl;
		return ;
	}
	i = 0;
	std::cout << std::endl;
	while (i < 8 && i < this->_index)
	{
		std::cout << "\x1b[94m" << std::setw(10) << i << "|" 
			<< std::setw(10) << str_long(this->_contacts[i].get_fname()) << "|"
			<< std::setw(10) << str_long(this->_contacts[i].get_lname()) << "|"
			<< std::setw(10) << str_long(this->_contacts[i].get_nickname())
			<< std::endl << NO_COLOR;
		i++;
	}
	std::cout << std::endl;
	while (!std::cin.eof() && str == "")
	{
		std::cout << "what contact would you like to check, give index: ";
		if (std::getline(std::cin, str) && str != "")
		{
			if (str.length() == 1 && (str[0] >= '0' && str[0] <= '7') && str[0] < '0' + this->_index)
			{
				i = str[0] - '0';
				break ;
			}
			if (str != "")
			{
				std::cout << YELLOW << "Invalid Index try again!" << NO_COLOR << std::endl;
				str = "";
			}
		}
	}
	std::cout << std::endl << BLUE << std::setw(18) << "First Name: " 
		<< this->_contacts[i].get_fname() << std::endl
		<< std::setw(18) << "Last Name: "
		<< this->_contacts[i].get_lname() << std::endl
		<< std::setw(18) << "Nickname: "
		<< this->_contacts[i].get_nickname() << std::endl
		<< std::setw(18) << "Phone number: "
		<< this->_contacts[i].get_phone_num() << std::endl << RED
		<< std::setw(18) << "Darkest secret: " << "\x1b[95m"
		<< this->_contacts[i].get_secret() << NO_COLOR << std::endl << std::endl;
}

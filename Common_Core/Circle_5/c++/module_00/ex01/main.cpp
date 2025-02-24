/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:16:23 by aminjauw          #+#    #+#             */
/*   Updated: 2023/06/21 16:41:29 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

int main(void)
{
	PhoneBook	p1;
	std::string	command;

	command = "";
	while(!command.size())
	{
		std::cout << "Please Enter Command: ";
		if(std::getline(std::cin, command), command != "")
		{
			if (!command.compare("ADD"))
			{
				p1.add();
				command = "";
			}
			else if (!command.compare("SEARCH"))
			{
				p1.search();
				command = "";
			}
			else if (!command.compare("EXIT"))
				break;
			else
			{
				std::cout << YELLOW << "Please put a valid command {ADD; SEARCH; EXIT}"
					<< std::endl << NO_COLOR;
				command = "";
			}
		}
	}
	return 0;
}
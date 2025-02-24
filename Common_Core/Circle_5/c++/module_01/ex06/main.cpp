/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:59:02 by aminjauw          #+#    #+#             */
/*   Updated: 2023/08/29 15:27:33 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	word(std::string str, std::string words[4])
{
	for (size_t i = 0; i < 4; i++)
	{
		if (str.compare(words[i]) == 0)
			return (i);
	}
	return (-1);
}

int	main( int argc, char **argv )
{
	Harl	annoying_custumer;
	std::string words[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
		
	if (argc != 2)
	{
		std::cout << "Wrong number of args" << std::endl;
		return 1;
	}
	std::string	str(argv[1]);
	while (true) {
		switch(word(str, words))
		{
			case -1:
				std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
				return 1;
			
			case 3:
				std::cout << "[ " << str << " ]" << std::endl;
				annoying_custumer.complain(str);
				std::cout << std::endl;
				return 0;
					
			default:
				std::cout << "[ " << str << " ]" << std::endl;
				annoying_custumer.complain(str);
				str = words[word(str, words) + 1];
				std::cout << std::endl;
		}
	}
	std::cout << str << std::endl;
}
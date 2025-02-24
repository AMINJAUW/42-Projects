/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:59:02 by aminjauw          #+#    #+#             */
/*   Updated: 2023/08/29 14:49:44 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main( void )
{
	Harl	annoying_custumer;
	
	while (true)
	{
		std::cout << "what level would you complain ? or would you like to stop ?; " << std::endl;
		std::string str;
		if (std::getline(std::cin, str))
		{
			if (str != "stop")
				annoying_custumer.complain(str);
			else
				break;
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:27:38 by aminjauw          #+#    #+#             */
/*   Updated: 2023/08/29 15:31:40 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl( void )
{
}

Harl::~Harl( void )
{
}
void	Harl::debug( void )
{
	std::cout << "I love having extra bacon for my ";
	std::cout << "7XL-double-cheese-triple-pickle-special-ketchup burger." << std::endl;
	std::cout << "I really do !" << std::endl;
}
void	Harl::info( void )
{
	std::cout << "I cannot believe adding extra bacon costs more money. " << std::endl;
	std::cout << "You didn’t put enough bacon in my burger !" << std::endl;
	std::cout << "If you did, I wouldn’t be asking for more !" << std::endl;
}


void	Harl::warning( void )
{
	std::cout << "I think I deserve to have some extra bacon for free. "<< std::endl;
	std::cout << "I’ve been coming for years whereas ";
	std::cout << "you started working here since last month." << std::endl;
}

void	Harl::error( void )
{
	std::cout << "This is unacceptable ! I want to speak to the manager now. " << std::endl;	
}

void	Harl::complain( std::string level )
{
	function_pointer fct[4] = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	std::string	message[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	for (int i = 0; i < 4; i++)
	{
		if (level == message[i])
		{
			(this->*(fct[i]))();
			return ;
		}
	}

	std::cout << "Wrong level of complain; you gave ; " << level << std::endl;
}


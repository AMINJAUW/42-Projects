/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:11:37 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/14 13:27:56 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(void) : _name("<name>")
{
	return ;
}

Zombie::~Zombie(void)
{
	std::cout << this->get_name() << ": is Destroyed" << std::endl;
	return ;
}

std::string	Zombie::get_name( void ) const
{
	return this->_name;
}

void	Zombie::set_name(std::string str)
{
	this->_name = str;
	return ;
}

void	Zombie::announce(void) const
{
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
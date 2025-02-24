/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:35:44 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/22 11:20:03 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap()
{
	cout << "Scaptrap Defautl constructor called ?" << endl;
}

ScavTrap::~ScavTrap(void)
{
	cout << "Scaptrap destroyed" << endl;
}

ScavTrap::ScavTrap(string name) : ClapTrap(name)
{
	this->_Hp = 100;
	this->_Ep = 50;
	this->_Att = 20;
	cout << "ScavTrap build" << endl; 
}

ScavTrap::ScavTrap(ScavTrap const &cpy)
{
	cout << "copy constructor called" << endl;
	*this = cpy;
}

ScavTrap	& ScavTrap::operator=(ScavTrap const & rhs)
{
	this->_Att = rhs.get_Att();
	this->_Ep = rhs.get_Ep();
	this->_Hp = rhs.get_Hp();
	this->_name = rhs.get_name();
	return *this;
}

void	ScavTrap::attack(string const & target)
{
	if (this->get_Hp() == 0 || this->get_Ep() == 0)
	{
		cout << YELLOW << this->get_name() << " ScavTrap doesn't look good enough to attack." << NO_COLOR << endl;
		return ;
	}
	this->_Ep--;
	if (this->get_Att() == 0)
	{
		cout << YELLOW << this->get_name() << " ScavTrap try to attack " << target << " but he does no domage :/" << NO_COLOR << endl;
		return;
	}
	cout << "ScavTrap " << this->get_name() << RED << " Attack " << YELLOW << target << \
	NO_COLOR << ", Causing " << RED << this->get_Att() << NO_COLOR << " points of damage !" << endl;
}
void	ScavTrap::guardGate()
{
	cout << "ScavTrap " << this->get_name() << " is now in Gatekeeper mode" << endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:02:31 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/22 12:33:57 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ScavTrap(), FragTrap()
{
	cout << "Default diamond constructor called" << endl;
}

DiamondTrap::~DiamondTrap()
{
	cout << "destroying diamond trap" << endl;
}

DiamondTrap::DiamondTrap(string const & name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name)
{
	this->_name = name;
	this->_Hp = FragTrap::_Hp;
	this->_Ep = ScavTrap::_Ep;
	this->_Att = FragTrap::_Att;
	return ;
}
DiamondTrap::DiamondTrap(const DiamondTrap &cpy) :ClapTrap(cpy), ScavTrap(cpy), FragTrap(cpy)
{
	*this = cpy;
}

DiamondTrap	& DiamondTrap::operator=(DiamondTrap const & rhs)
{
	this->_name = rhs.get_name();
	this->_Att = rhs.get_Att();
	this->_Ep = rhs.get_Ep();
	this->_Hp = rhs.get_Hp();
	return *this;
}

void DiamondTrap::whoAmI()
{
	cout << "DiamondTrap name = " << this->_name << endl;
	cout << "ClapTrap name = " << this->get_name() << endl;
}
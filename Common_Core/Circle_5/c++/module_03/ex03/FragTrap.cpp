/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:36:16 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/22 12:34:54 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(void) : ClapTrap()
{
	cout << "FragTrap Defautl constructor called ?" << endl;
}

FragTrap::~FragTrap(void)
{
	cout << "FragTrap destroyed" << endl;
}

FragTrap::FragTrap(string name) : ClapTrap(name)
{
	this->_Hp = 100;
	this->_Ep = 100;
	this->_Att = 30;
	cout << "FragTrap build" << endl; 
}

FragTrap::FragTrap(FragTrap const &cpy)
{
	cout << "FragTrap copy constructor called" << endl;
	*this = cpy;
}

FragTrap	& FragTrap::operator=(FragTrap const & rhs)
{
	this->_Att = rhs.get_Att();
	this->_Ep = rhs.get_Ep();
	this->_Hp = rhs.get_Hp();
	this->_name = rhs.get_name();
	return *this;
}

void	FragTrap::highFivesGuys(void)
{
	cout << this->get_name() << " FragTrap wants to high five you" << endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:27:17 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/22 11:21:46 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void) : _name("/!\\HACKER_CLAP_TRAP/!\\"), _Hp(10), _Ep(10), _Att(0)
{
	cout << "How did you use the Default constructor ?? it's suppose to be private..." << endl;
}

ClapTrap::ClapTrap(ClapTrap const & cpy)
{
	cout << "Creating a ClapTrap copy" << endl;
	*this = cpy;
}

ClapTrap::ClapTrap(string name) : _name(name), _Hp(10), _Ep(10), _Att(0)
{
	cout << name << " joined the community of ClapTrap. Please Welcome him well." << endl;
}

ClapTrap::~ClapTrap(void)
{
	cout << "end of ClapTrap " << this->_name << ", We wish him farewell :p" << endl; 
}

ClapTrap	& ClapTrap::operator=(ClapTrap const & rhs)
{
	this->_name = rhs.get_name();
	this->_Att = rhs.get_Att();
	this->_Ep = rhs.get_Ep();
	this->_Hp = rhs.get_Hp();
	return *this;
}

/*---- ACCESSORS -----*/

string	ClapTrap::get_name(void) const
{
	return this->_name;
}

unsigned int	ClapTrap::get_Hp(void) const
{
	return this->_Hp;
}

unsigned int	ClapTrap::get_Ep(void) const
{
	return this->_Ep;
}

unsigned int	ClapTrap::get_Att(void) const
{
	return this->_Att;
}

/*-------- Actions -----------*/

void ClapTrap::attack(const std::string & target)
{
	if (this->get_Hp() == 0 || this->get_Ep() == 0)
	{
		cout << YELLOW << this->get_name() << " doesn't look good enough to attack." << NO_COLOR << endl;
		return ;
	}
	this->_Ep--;
	if (this->get_Att() == 0)
	{
		cout << YELLOW << this->get_name() << " try to attack " << target << " but he does no domage :/" << NO_COLOR << endl;
		return;
	}
	cout << "ClapTrap " << this->get_name() << RED << " Attack " << YELLOW << target << \
	NO_COLOR << ", Causing " << RED << this->get_Att() << NO_COLOR << " points of damage !" << endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (this->get_Hp() == 0)
	{
		cout << YELLOW <<"Why are you trying to dammage an already dead ClapTrap ?" << YELLOW << endl;
		return ;
	}
	else if (amount == 0)
	{
		cout << YELLOW << "Why attack with 0 dammage ?" << endl;
		return ;
	}
	cout << "ClapTrap " << this->get_name() << " takes " << RED << amount << NO_COLOR << " dammage !" << endl;
	this->_Hp = this->get_Hp() > amount ? this->get_Hp() - amount : 0;
	cout << "ClapTrap " << this->get_name() << "has now " << YELLOW << this->get_Hp() << NO_COLOR << " Hit Points (HP)" << endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (this->get_Hp() == 0 || this->get_Ep() == 0)
	{
		cout << YELLOW << this->get_name() << " doesn't look good enough to repair itself." << NO_COLOR << endl;
		return ;
	}
	this->_Ep--;
	if (amount == 0)
	{
		cout << YELLOW << "Why repair with 0 dammage ? it still costed 1 Ep for your mistake" << endl;
		return ;
	}
	cout << "ClapTrap " << this->get_name() <<" repaired himself for " << GREEN << amount << NO_COLOR << endl;
	if (UINT_MAX - amount < this->get_Hp())
	{
		cout << YELLOW << "TOO MUCH HP..." << endl;
		this->_Hp = UINT_MAX;
		return ;
	} 
	this->_Hp += amount;
	return ;
}

std::ostream	& operator<<(std::ostream & o, ClapTrap const &rhs)
{
	o << YELLOW << "________ClapTrap " << rhs.get_name() <<"_____________\n" << NO_COLOR << endl;
	o << "Hit Points (HP) = " << GREEN;
	if (rhs.get_Hp() < 5)
		o << RED;
	o << rhs.get_Hp() << NO_COLOR << endl;
	o << "Energy Points (EP) = " << YELLOW << rhs.get_Ep() << NO_COLOR << endl;
	o << "Attack Points (Att) = " << GREEN;
	if (rhs.get_Att() < 10)
		o << (rhs.get_Att() < 5 ? RED : YELLOW);
	o << rhs.get_Att() << NO_COLOR << endl;
	return o;
}
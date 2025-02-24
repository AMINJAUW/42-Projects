/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:19:43 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/14 16:50:54 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(string name) : _name(name), _weapon(nullptr)
{	
}
HumanB::~HumanB(void)
{
}

void	HumanB::attack(void) const
{
	string	weapon_name;
	
	if (this->_weapon == nullptr)
		weapon_name = "hands if he or she has hands";
	else
		weapon_name = this->_weapon->getType();
	cout << this->_name << " attacks with their " << weapon_name << endl;
}

void	HumanB::setWeapon(Weapon &weapon)
{
	this->_weapon = &weapon;
}
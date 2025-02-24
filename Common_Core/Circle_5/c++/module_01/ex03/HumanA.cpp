/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:12:18 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/14 16:32:47 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(string name, Weapon &weapon) : _name(name), _weapon(weapon)
{	
}
HumanA::~HumanA(void)
{
}

void	HumanA::attack(void) const
{
	cout << this->_name << " attacks with their " << this->_weapon.getType() << endl;
}
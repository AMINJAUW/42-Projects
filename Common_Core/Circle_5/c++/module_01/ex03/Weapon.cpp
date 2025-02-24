/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:55:12 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/14 16:32:47 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(string type) : _type(type)
{
}

Weapon::~Weapon(void) {
}

string const & Weapon::getType(void) const {
	return this->_type;
}

void	Weapon::setType(string str){
	this->_type = str;
}


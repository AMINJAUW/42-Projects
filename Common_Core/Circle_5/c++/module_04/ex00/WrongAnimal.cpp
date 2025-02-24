/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:23:30 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/24 12:33:15 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) : _type("unknown")
{
	cout << "creating WrongAnimal of type unknown" << endl;
}

WrongAnimal::~WrongAnimal(void)
{
	cout << "Destroying WrongAnimal" << endl;
}

WrongAnimal::WrongAnimal(WrongAnimal const &rhs)
{
	cout << "Copy WrongAnimal constructor called" << endl;
	*this = rhs;
}

WrongAnimal	& WrongAnimal::operator=(WrongAnimal const & rhs)
{
	this->_type = rhs.getType();
	return *this;
}

string WrongAnimal::getType(void) const
{
	return this->_type;
}

void WrongAnimal::makeSound(void) const
{
	cout << "unknown WrongAnimal make weird noses" << endl;	
}
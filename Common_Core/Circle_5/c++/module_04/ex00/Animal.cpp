/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:09:51 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/24 12:32:15 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(void) : _type("unknown")
{
	cout << "creating Animal of type unknown" << endl;
}

Animal::~Animal(void)
{
	cout << "Destroying Animal" << endl;
}

Animal::Animal(Animal const &rhs)
{
	cout << "Copy Animal constructor called" << endl;
	*this = rhs;
}

Animal	& Animal::operator=(Animal const & rhs)
{
	this->_type = rhs.getType();
	return *this;
}

string Animal::getType(void) const
{
	return this->_type;
}

void Animal::makeSound(void) const
{
	cout << "unknown Animal make weird noses" << endl;	
}



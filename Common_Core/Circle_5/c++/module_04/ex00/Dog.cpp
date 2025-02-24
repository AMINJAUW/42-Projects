/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:22:26 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/24 12:33:09 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void)
{
	this->_type = "Dog";
	cout << "creating Dog" << endl;
}

Dog::~Dog(void)
{
	cout << "Destroying Dog" << endl;
}

Dog::Dog(Dog const &rhs)
{
	cout << "Copy Dog constructor called" << endl;
	*this = rhs;
}

Dog	& Dog::operator=(Dog const & rhs)
{
	this->_type = rhs.getType();
	return *this;
}

string Dog::getType(void) const
{
	return this->_type;
}

void Dog::makeSound(void) const
{
	cout << "Wouf Wouf..." << endl;	
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:22:26 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/24 15:06:25 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void)
{
	this->brain = new Brain();
	this->_type = "Dog";
	cout << "creating Dog" << endl;
}

Dog::~Dog(void)
{
	delete this->brain;
	cout << "Destroying Dog" << endl;
}

Dog::Dog(Dog const &rhs)
{
	this->_type = rhs.getType();
	this->brain = new Brain(*(rhs.getBrain()));
	cout << "Copy Dog constructor called, with his own brain" << endl;
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

Brain *Dog::getBrain( void ) const
{
	return (this->brain);
}


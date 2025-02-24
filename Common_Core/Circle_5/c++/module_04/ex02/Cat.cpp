/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:09:51 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/24 14:47:33 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void)
{
	this->_type = "cat";
	this->brain = new Brain;
	cout << "creating Cat" << endl;
}

Cat::~Cat(void)
{
	delete this->brain;
	cout << "Destroying Cat" << endl;
}

Cat::Cat(Cat const &rhs)
{
	this->_type = rhs.getType();
	this->brain = new Brain(*(rhs.getBrain()));
	std::cout << "A cat was constructed from copy, but has a brain on its own\n";
}

Cat	& Cat::operator=(Cat const & rhs)
{
	this->_type = rhs.getType();
	return *this;
}

string Cat::getType(void) const
{
	return this->_type;
}

void Cat::makeSound(void) const
{
	cout << "MIAAAOUUUUWW....." << endl;	
}

Brain *Cat::getBrain( void ) const
{
	return (this->brain);
}

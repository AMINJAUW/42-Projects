/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:09:51 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/24 12:33:02 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void)
{
	this->_type = "cat";
	cout << "creating Cat" << endl;
}

Cat::~Cat(void)
{
	cout << "Destroying Cat" << endl;
}

Cat::Cat(Cat const &rhs)
{
	cout << "Copy Cat constructor called" << endl;
	*this = rhs;
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



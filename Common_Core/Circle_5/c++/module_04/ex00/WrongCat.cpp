/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:27:29 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/24 12:33:22 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(void)
{
	this->_type = "Wrongcat";
	cout << "creating WrongCat" << endl;
}

WrongCat::~WrongCat(void)
{
	cout << "Destroying WrongCat" << endl;
}

WrongCat::WrongCat(WrongCat const &rhs)
{
	cout << "Copy WrongCat constructor called" << endl;
	*this = rhs;
}

WrongCat	& WrongCat::operator=(WrongCat const & rhs)
{
	this->_type = rhs.getType();
	return *this;
}

string WrongCat::getType(void) const
{
	return this->_type;
}

void WrongCat::makeSound(void) const
{
	cout << "Wrong MIAAAOUUUUWW....." << endl;	
}
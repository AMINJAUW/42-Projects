/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:01:35 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/26 16:47:21 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice()
{
	this->_type = "ice";
}

Ice::Ice(Ice const & cpy)
{
	*this = cpy;
}

Ice::~Ice()
{}

Ice	& Ice::operator=(Ice const & cpy)
{
	this->_type = cpy.getType();
	return *this;
}

Ice*	Ice::clone(void) const
{
	return new Ice();
}
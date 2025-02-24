/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:45:11 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/26 16:47:08 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure()
{
	this->_type = "cure";
}

Cure::Cure(Cure const & cpy)
{
	*this = cpy;
}

Cure::~Cure()
{}

Cure	& Cure::operator=(Cure const & cpy)
{
	this->_type = cpy.getType();
	return *this;
}

Cure*	Cure::clone(void) const
{
	return new Cure();
}
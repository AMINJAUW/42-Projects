/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:48:28 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/20 14:23:04 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int const Fixed::_frac_bits = 8;

Fixed::Fixed(void) : _raw_bits(0)
{
	cout << "Default constructor called" << endl;
}

Fixed::Fixed(const Fixed &cpy)
{
	cout << "Copy constructor called" << endl;
	*this = cpy;
}

Fixed::~Fixed(void)
{
	cout << "Destructor called" << endl;
}

Fixed & Fixed::operator=(Fixed const & rhs)
{
	cout << "Copy assignment called" << endl;
	this->_raw_bits = rhs.getRawBits();
	return *this;
}

int		Fixed::getRawBits(void) const
{
	cout << "getRawBits member function called" << endl;
	return this->_raw_bits;
}

void	Fixed::setRawBits(int const raw)
{
	cout << "setRawBits member function called" << endl;
	this->_raw_bits = raw;
	return ;
}


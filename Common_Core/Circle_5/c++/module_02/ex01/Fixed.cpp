/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:48:28 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/21 12:40:16 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"


Fixed::Fixed(void) : _raw_bits(0)
{
	cout << "Default constructor called" << endl;
}

Fixed::Fixed(const Fixed &cpy)
{
	cout << "Copy constructor called" << endl;
	*this = cpy;
}

Fixed::Fixed(const int n) : _raw_bits(n * (1 << _frac_bits))
{
	if (n > INT_MAX >> _frac_bits)
		throw std::invalid_argument("Value is to big and will overflow, reduce value or the floating point number");
	cout << "Int constructor called" << endl;
}

Fixed::Fixed(const float f) : _raw_bits(roundf(f * (1 << _frac_bits)))
{
	if (roundf(f) > INT_MAX >> _frac_bits)
		throw std::invalid_argument("Value is to big and will overflow, reduce value or the floating point number");
	cout << "Float constructor called" << endl;
}

Fixed::~Fixed(void)
{
	cout << "Destructor called" << endl;
}

Fixed & Fixed::operator=(Fixed const & rhs)
{
	cout << "Copy assignment operator called" << endl;
	this->_raw_bits = rhs.getRawBits();
	return *this;
}

int		Fixed::getRawBits(void) const
{
	return this->_raw_bits;
}

void	Fixed::setRawBits(int const raw)
{
	this->_raw_bits = raw;
	return ;
}

float Fixed::toFloat( void ) const
{
	float f = static_cast <float> (this->getRawBits());
	f /= (1 << _frac_bits);
	
	return f;
}

int Fixed::toInt( void ) const
{
	float f = static_cast <float> (this->getRawBits());
	f /= (1 << _frac_bits);
	
	return static_cast <int> (roundf(f));
}

std::ostream & operator<<(std::ostream & o, Fixed const & rhs)
{
	o << rhs.toFloat();
	return o;
}
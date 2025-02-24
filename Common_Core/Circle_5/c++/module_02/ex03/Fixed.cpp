/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:48:28 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/21 16:17:17 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"


Fixed::Fixed(void) : _raw_bits(0)
{
}

Fixed::Fixed(const Fixed &cpy)
{
	*this = cpy;
}

Fixed::Fixed(const int n) : _raw_bits(n * (1 << _frac_bits))
{
	if (n > INT_MAX >> _frac_bits || n < INT_MIN >> _frac_bits)
		throw std::invalid_argument("Value is to big and will overflow or underflow, reduce value or the floating point number");
}

Fixed::Fixed(const float f) : _raw_bits(roundf(f * (1 << _frac_bits)))
{
	if (roundf(f) > INT_MAX >> _frac_bits || roundf(f) < INT_MIN >> _frac_bits)
		throw std::invalid_argument("Value is to big and will overflow, reduce value or the floating point number");
}

Fixed::~Fixed(void)
{
}

Fixed & Fixed::operator=(Fixed const & rhs)
{
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

/*------------------ COMPARAISONS -------------------*/

bool	Fixed::operator>(Fixed const & rhs) const
{
	return this->_raw_bits > rhs.getRawBits(); 
}

bool	Fixed::operator<(Fixed const & rhs) const
{
	return this->_raw_bits < rhs.getRawBits(); 
}

bool	Fixed::operator>=(Fixed const & rhs) const
{
	return this->_raw_bits >= rhs.getRawBits(); 
}

bool	Fixed::operator<=(Fixed const & rhs) const
{
	return this->_raw_bits <= rhs.getRawBits(); 
}

bool	Fixed::operator==(Fixed const & rhs) const
{
	return this->_raw_bits == rhs.getRawBits(); 
}

bool	Fixed::operator!=(Fixed const & rhs) const
{
	return this->_raw_bits != rhs.getRawBits(); 
}

/*------------------OPERATIONS----------------------*/

Fixed	Fixed::operator+(Fixed const & rhs) const
{
	float result = (this->_raw_bits + rhs.getRawBits()) / (1 << _frac_bits);
	return Fixed(result);
}

Fixed	Fixed::operator-(Fixed const & rhs) const
{
	float result = (this->_raw_bits - rhs.getRawBits()) / (1 << _frac_bits);
	return Fixed(result);
}

Fixed	Fixed::operator*(Fixed const & rhs) const
{
	float result = (this->toFloat() * rhs.toFloat());
	return Fixed(result);
}

Fixed	Fixed::operator/(Fixed const & rhs) const
{
	if (rhs.getRawBits() == 0)
	{
		cout << "ERROR division by 0" << endl;
		return Fixed(0);
	}
	float result = (this->toFloat() / rhs.toFloat());
	return Fixed(result);
}

/*-------------------INCREMENTATION---------------------*/

Fixed & Fixed::operator++(void)
{
	this->_raw_bits++;
	return *this;
}

Fixed & Fixed::operator--(void)
{
	this->_raw_bits--;
	return *this;
}

Fixed	Fixed::operator++(int)
{
	Fixed	temp(*this);
	this->_raw_bits++;
	return	temp;
}

Fixed	Fixed::operator--(int)
{
	Fixed	temp(*this);
	this->_raw_bits--;
	return	temp;	
}

/*----------------------STATIC FUNCTIONS-----------------*/

Fixed	& Fixed::min(Fixed &a, Fixed &b)
{
	if (a <= b)
		return (a);
	return (b);
}
Fixed	& Fixed::max(Fixed &a, Fixed &b)
{
	if (a >= b)
		return (a);
	return (b);	
}
const Fixed	& Fixed::min(const Fixed &a, const Fixed &b)
{
	if (a <= b)
		return (a);
	return (b);	
}

const Fixed	& Fixed::max(const Fixed &a, const Fixed &b)
{
	if (a >= b)
		return (a);
	return (b);	
}
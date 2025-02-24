/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:32:15 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/21 13:32:23 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.hpp"

Vector::Vector(void)
{
}

Vector::~Vector()
{
}

Vector::Vector(Vector const &cpy)
{
	*this = cpy;
}

Vector::Vector(Point const &a, Point const &b) : _v(Point(b.get_x() - a.get_x(), b.get_y() - a.get_y()))
{
}

Vector::Vector(Point const & composante) : _v(composante)
{
}

Vector &Vector::operator=(Vector const &rhs)
{
	this->_v = rhs._v;
	return *this;
}

Fixed	Vector::dot_product(Vector const &rhs) const
{
	return (this->_v.get_x() * rhs._v.get_x()) + (this->_v.get_y() * rhs._v.get_y());
}

Vector	&Vector::perpendicular(Vector const	& towards)
{
	Vector	temp(Point(this->_v.get_y(), this->_v.get_x() * Fixed(-1)));

	if (towards.dot_product(temp) > Fixed(0))
		*this = temp;
	else
		*this = temp.inverse_vector();
	return *this;
}

Point	Vector::get_v(void) const
{
	return this->_v;
}

Fixed	Vector::get_length(void) const
{
	return Fixed(std::sqrtf(this->dot_product(*this).toFloat()));
}

Vector	& Vector::inverse_vector(void)
{
	this->_v = Point(this->_v.get_x() * Fixed(-1), this->_v.get_y() * Fixed(-1));
	return *this;
}

std::ostream & operator<<(std::ostream & o, Vector const & rhs)
{
	o << rhs.get_v();
	return o;
}
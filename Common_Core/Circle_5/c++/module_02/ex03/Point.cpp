/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:07:15 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/21 16:31:15 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point(void) : x(Fixed(0)), y(Fixed(0))
{
}

Point::Point(Point const & rhs)
{
	*this = rhs;
}

Point::Point(float const x, float const y) : x(Fixed(x)), y(Fixed(y)) 
{
}

Point::Point(Fixed const x, Fixed const y) : x(x), y(y) 
{
}

Point::~Point(void)
{
}

Point	&Point::operator=(Point const &rhs)
{
	this->~Point();
	new(this) Point(rhs.get_x(), rhs.get_y()); //new(this) reallocate memory at *this so still on the stack so no need to delete
	return *this;
}

Fixed	Point::get_x(void) const
{
	return this->x;
}

Fixed	Point::get_y(void) const
{
	return this->y;
}

std::ostream & operator<<(std::ostream & o, Point const & p)
{
	o << "(" << p.get_x() << ", " << p.get_y() << ")";
	return o;
}

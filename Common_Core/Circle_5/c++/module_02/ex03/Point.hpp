/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:00:40 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/21 16:29:45 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

class Point {

private :

	Fixed const x;
	Fixed const y;

public :

	Point(void);
	Point(float const x, float const y);
	Point(Fixed const x, Fixed const y);
	Point(Point const &cpy);
	~Point(void);
	
	Point & operator=(Point const & rhs);

	/* Accessors */
	Fixed get_x(void) const;
	Fixed get_y(void) const;
};

std::ostream & operator<<(std::ostream & o, Point const & p);

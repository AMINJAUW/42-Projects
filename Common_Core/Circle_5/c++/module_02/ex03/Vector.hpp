/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:31:38 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/21 17:57:36 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "Point.hpp"

class Vector
{
private:
	Point _v;
	Vector(void);
public:
	Vector(Vector const &cpy);
	Vector(Point const &a, Point const &b);
	Vector(Point const &composantes);
	~Vector();

	Vector	& operator=(Vector const &rhs);
	Fixed	dot_product(Vector const &rhs) const;
	Vector	& perpendicular(Vector const & towards);
	Fixed	get_length(void) const;

	Point	get_v(void) const;
	Vector	& inverse_vector(void);
};

std::ostream & operator<<(std::ostream & o, Vector const & rhs);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:15:55 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/21 18:48:15 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.hpp"


bool bsp( Point const a, Point const b, Point const c, Point const point)
{
	Vector	a_p(a, point);
	Vector	b_p(b, point);
	Vector	perpendicular_ab(Vector(a, b).perpendicular(Vector(a, c)));
	Vector	perpendicular_ac(Vector(a, c).perpendicular(Vector(a, b)));
	Vector	perpendicular_bc(Vector(b, c).perpendicular(Vector(b, a)));

	if (Vector(a, b).dot_product(Vector(a, c)) == Vector(a, b).get_length() * Vector(a, c).get_length())
		throw std::invalid_argument("\nNot a valid triangle, the 3 points are aligned\n");
	if (perpendicular_ab.dot_product(a_p) >= Fixed(0)
		&& perpendicular_ac.dot_product(a_p) >= Fixed(0)
		&& perpendicular_bc.dot_product(b_p) >= Fixed(0))
		return (true);
	return (false);
}
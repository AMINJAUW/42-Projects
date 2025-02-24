/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_and_cross_product.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:47:52 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/23 11:48:36 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
Produit scalaire
u . v
*/
double	dot_poduct(t_coordinates v1, t_coordinates v2)
{
	double	sum;

	sum = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (sum);
}

/*
Produit vecctoriel
v X u = w
or
v ∧ u = w
with w ⊥ to v and to u
*/
t_coordinates	cross_product(t_coordinates v1, t_coordinates v2)
{
	t_coordinates	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

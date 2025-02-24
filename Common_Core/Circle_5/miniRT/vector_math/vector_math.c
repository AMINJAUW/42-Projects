/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:29:53 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/07 16:45:49 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coordinates	mult_vector(double a, t_coordinates v)
{
	t_coordinates	result;

	result.x = a * v.x;
	result.y = a * v.y;
	result.z = a * v.z;
	return (result);
}

t_coordinates	sum_diff_vector(t_coordinates v1, t_coordinates v2, int sum)
{
	t_coordinates	result;

	result.x = v1.x + (sum * v2.x); 
	result.y = v1.y + (sum * v2.y);
	result.z = v1.z + (sum * v2.z);
	return (result);
}

double	squared_norm(t_coordinates v)
{
	return (dot_poduct(v, v));
}

t_coordinates	normalize_vector(t_coordinates v)
{
	double			norm;
	t_coordinates	result;

	norm = sqrt(dot_poduct(v, v));
	result.x = v.x / norm;
	result.y = v.y / norm;
	result.z = v.z / norm;
	return (result);
}

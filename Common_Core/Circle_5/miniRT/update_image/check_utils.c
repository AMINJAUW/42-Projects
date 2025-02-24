/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:35:17 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/07 18:42:39 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
takes as input a b and c such as
ax^2 + bx + c = 0
and resolve for real values of x
if delta < 0 return NULL
if delta == 0
the 2 values of x are the same
*/
double	*quadratic_solution(double x[2], double abc[3])
{
	double	delta;

	delta = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (delta < 0)
		return (NULL);
	x[0] = (-abc[1] - sqrt(delta)) / (2 * abc[0]);
	x[1] = (-abc[1] + sqrt(delta)) / (2 * abc[0]);
	return (x);
}

void	update_data_info(void *obj_ptr, t_color_finder *data,
	double *t_value, double new_t)
{
	*t_value = new_t;
	if (data->checking_light == TRUE)
		return ;
	data->point_seen = sum_diff_vector(data->origin,
			mult_vector(new_t, data->line_vector), SUM);
	data->object_addr = obj_ptr;
}

double	sign_of(double n)
{
	if (n < 0)
		return (-1);
	return (1);
}

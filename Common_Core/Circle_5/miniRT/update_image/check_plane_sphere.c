/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane_sphere.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:38:20 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/08 11:59:49 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
we need to solve the equation for t
to find the	point(s) where the sphere and the line meet.

(x(t) - Cx)^2 + (y(t) - Cy)^2 + (z(t) - Cz)^2 = r^2
with C beeing the center of the sphere
x(t) = x0 + vx * t
...
x0 ,y0, z0 the coord. of the camera
v = (vx, vy, vz) the composantes of the normed vector to the screen pixel

After syplification we find that ;
|v|^2 t^2 + 2(X.v)t + |X|^2 - R^2 = 0
With : X = (x0 - Cx, y0 - Cy, z0 - Cz)
and now we can use the quadratic equation to find the value of t
*/
void	check_sphere(t_sphere *sphere, t_color_finder *data, double *t_value)
{
	double			new_t[2];
	double			abc[3];
	t_coordinates	x;

	x = sum_diff_vector(data->origin, sphere->coordinates, DIFF);
	abc[0] = squared_norm(data->line_vector);
	abc[1] = 2 * dot_poduct(x, data->line_vector);
	abc[2] = squared_norm(x) - pow(sphere->diameter / 2.0, 2);
	if (quadratic_solution(new_t, abc) == NULL)
		return ;
	if (new_t[0] >= 0 && !(*t_value != -1
			&& (new_t[0] > *t_value || almosteq(new_t[0], *t_value))))
		update_data_info((void *)sphere, data, t_value, new_t[0]);
	else if (new_t[1] >= 0 && !(*t_value != -1
			&& (new_t[1] > *t_value || almosteq(new_t[1], *t_value))))
		update_data_info((void *)sphere, data, t_value, new_t[1]);
	else
		return ;
	if (data->checking_light == TRUE)
		return ;
	data->normal_vector_of_object_from_point = mult_vector(
			-1 * sphere->camera_inside, normalize_vector(sum_diff_vector(
					data->point_seen, sphere->coordinates, DIFF)));
	data->color = sphere->color;
	return ;
}

void	check_plane(t_plane *plane, t_color_finder *data, double *t_value)
{
	t_coordinates	x;
	t_coordinates	n;
	t_coordinates	v;
	double			t;
	double			v_dot_n;

	v = data->line_vector;
	n = plane->vector;
	v_dot_n = dot_poduct(v, n);
	if (v_dot_n == 0)
		return ;
	x = sum_diff_vector(data->origin, plane->coordinates, DIFF);
	t = -dot_poduct(x, n) / v_dot_n;
	if (t < 0)
		return ;
	if (!(*t_value != -1 && (t > *t_value || almosteq(t, *t_value))))
	{
		update_data_info((void *)plane, data, t_value, t);
		if (data->checking_light == TRUE)
			return ;
		data->normal_vector_of_object_from_point = mult_vector(-1
				* sign_of(dot_poduct(plane->vector, data->line_vector)),
				plane->vector);
		data->color = plane->color;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:40:21 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/07 19:41:36 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	calculate_new_t(t_cylinder *cylinder, double *h,
	t_coordinates *n, t_color_finder *data)
{
	t_coordinates	v;
	t_coordinates	x;
	double			new_t;

	v = data->line_vector;
	if (dot_poduct(v, *n) == 0)
		return (-1);
	*h = fmin(*h, cylinder->height);
	*h = fmax(*h, 0);
	x = sum_diff_vector(data->origin, sum_diff_vector(cylinder->bottom_center,
				mult_vector(*h, cylinder->vector), SUM), DIFF);
	if (*h == 0)
		*n = mult_vector(-1, *n);
	new_t = -1 * dot_poduct(x, *n) / dot_poduct(v, *n);
	return (new_t);
}

int	go_through_disk(t_cylinder *cylinder, t_color_finder *data,
		double h, double *t_value)
{
	double			new_t;
	t_coordinates	n;
	double			d_center_disk;

	n = cylinder->vector;
	new_t = calculate_new_t(cylinder, &h, &n, data);
	if (new_t < 0)
		return (FALSE);
	d_center_disk = squared_norm(sum_diff_vector(sum_diff_vector(data->origin,
					mult_vector(new_t, data->line_vector), SUM),
				sum_diff_vector(cylinder->bottom_center,
					mult_vector(h, cylinder->vector), SUM), DIFF));
	if (d_center_disk <= pow(cylinder->diameter / 2, 2))
	{
		if (*t_value != -1 && (new_t > *t_value || almosteq(new_t, *t_value)))
			return (FALSE);
		update_data_info((void *)cylinder, data, t_value, new_t);
		if (data->checking_light == FALSE)
			data->normal_vector_of_object_from_point = mult_vector(
					-1 * cylinder->camera_inside, n);
		return (TRUE);
	}
	else
		return (FALSE);
}

int	check_cylinder_t(double *t_value, double t, 
	t_color_finder *data, t_cylinder *cylinder)
{
	double			h;
	t_coordinates	n;
	t_coordinates	v;

	n = cylinder->vector;
	v = data->line_vector;
	h = dot_poduct(sum_diff_vector(sum_diff_vector(mult_vector(t, v),
					data->origin, SUM), cylinder->bottom_center, DIFF), n);
	if (t >= 0 && h >= 0 && h <= cylinder->height)
	{
		if (*t_value != -1 && (t > *t_value || almosteq(t, *t_value)))
			return (FALSE);
		update_data_info((void *)cylinder, data, t_value, t);
		if (data->checking_light == FALSE)
			data->normal_vector_of_object_from_point = mult_vector(
					-1 * cylinder->camera_inside, normalize_vector(
						sum_diff_vector(data->point_seen, sum_diff_vector(
								cylinder->bottom_center, mult_vector(
									h, cylinder->vector), SUM), DIFF)));
		return (TRUE);
	}
	return (go_through_disk(cylinder, data, h, t_value));
}

/*
we need to solve the equation for t
to find the	point(s) where the cylinder and the line meet.

(vt + X).(vt + X) - ((v.t + X)|n)^2 - r^2 = 0
with
C the coord of the cylinder
line = O + vt ; O = (x0, y0, z0)
X = C - O = (x0 - Cx, y0 - Cy, z0 - Cz)

we can rewrite it as
at^2 + bt +c = 0
this is abc[3] values;
We then can find the values of t
if a value of t is not negative we check if it's height in the cylinder
is between 0 and cylinder height.
this can be done with
h = (vt + X)|n
if h is not in the interval {0, h_max}
check if the line intesect with the plane a the top or bottom of the plane 
(top if h > h_max and conversely)
with the equation
(vt + X)|n = 0 if top or (vt + X)|-n = 0 if bottom
/!\ t = -/+ (X|n) / (v|n)
if (v | n) = 0 
=> v is perpendicular to n 
so it we are on the brim of the cylinder h = h_max
so we are not checkin for the plane 
and it should not be taken as a point if we are.
we can direcly check if t is poisitive 
only if the signs of (X|n) and (v|n) are different (or the same with h < 0)
*/
void	check_cylinder(t_cylinder *cylinder,
	t_color_finder *data, double *t_value)
{
	double			new_t[2];
	double			abc[3];
	t_coordinates	x;

	x = sum_diff_vector(data->origin, cylinder->bottom_center,
			DIFF);
	abc[0] = squared_norm(data->line_vector)
		- pow(dot_poduct(data->line_vector, cylinder->vector), 2);
	abc[1] = 2 * (dot_poduct(data->line_vector, x)
			- (dot_poduct(data->line_vector, cylinder->vector) * dot_poduct(x,
					cylinder->vector)));
	abc[2] = squared_norm(x) - pow(dot_poduct(x, cylinder->vector), 2)
		- pow(cylinder->diameter / 2, 2);
	if (quadratic_solution(new_t, abc) == NULL)
		return ;
	if ((check_cylinder_t(t_value, new_t[0], data, cylinder) == TRUE
			|| check_cylinder_t(t_value, new_t[1], data, cylinder) == TRUE)
		&& data->checking_light == FALSE)
		data->color = cylinder->color;
}

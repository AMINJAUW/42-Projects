/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:36:45 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/08 11:59:07 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_list	*checking_object(t_color_finder *data,
	t_list *checking, int object, double *t_value)
{
	if (checking->content == data->object_addr)
		return (checking->next);
	if (on_object(data, checking, object))
		return (checking->next);
	if (object == SPHERE)
		check_sphere((t_sphere *)checking->content, data, t_value);
	else if (object == PLANE)
		check_plane((t_plane *)checking->content, data, t_value);
	else if (object == CYLINDER)
		check_cylinder((t_cylinder *)checking->content, data, t_value);
	return (checking->next);
}

int	point_sees_light(t_scene *scene, t_color_finder *data)
{
	double	t_value;
	double	distance_to_light;
	t_list	*checking;

	t_value = -1;
	data->origin = data->point_seen;
	distance_to_light = sqrt(squared_norm(
				sum_diff_vector(scene->spot_lighting->coordinates,
					data->point_seen, DIFF)));
	checking = scene->spheres;
	while (checking != NULL)
		checking = checking_object(data, checking, SPHERE, &t_value);
	checking = scene->planes;
	while (checking != NULL)
		checking = checking_object(data, checking, PLANE, &t_value);
	checking = scene->cylinders;
	while (checking != NULL)
		checking = checking_object(data, checking, CYLINDER, &t_value);
	if (t_value <= 0 || t_value > distance_to_light)
		return (TRUE);
	return (FALSE);
}

void	update_gamma(t_scene *scene, t_color_finder *data)
{
	double	n_dot_l;

	data->line_vector = normalize_vector(
			sum_diff_vector(scene->spot_lighting->coordinates,
				data->point_seen, DIFF));
	n_dot_l = dot_poduct(data->line_vector,
			data->normal_vector_of_object_from_point);
	if (n_dot_l < 0 || point_sees_light(scene, data) == FALSE)
		return ;
	data->gamma = fmin(1,
			data->gamma + scene->spot_lighting->brightness * n_dot_l);
	return ;
}

t_color	diminish_brightness(t_color color, double gamma)
{
	color.blue = color.blue * gamma;
	color.green = color.green * gamma;
	color.red = color.red * gamma;
	return (color);
}

void	calculate_color(t_scene *scene, t_color_finder *data)
{
	data->gamma = scene->ambient_lighting->ratio;
	if (scene->spot_lighting != NULL && has_light(scene, data))
		update_gamma(scene, data);
	data->color = diminish_brightness(data->color, data->gamma);
}

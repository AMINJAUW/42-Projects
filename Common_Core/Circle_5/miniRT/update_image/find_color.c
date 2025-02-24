/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:19:07 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/08 12:00:19 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coordinates	calculate_pixel_vector(t_camera *camera, int x, int y)
{
	t_coordinates		v;
	t_coordinates		x_coord;
	t_coordinates		xy_coord;
	t_coordinates		screen_center;

	screen_center = sum_diff_vector(camera->coordinates,
			mult_vector(camera->screen_distance, camera->vector), SUM);
	x_coord = sum_diff_vector(screen_center,
			mult_vector(x, camera->right_vector), SUM);
	xy_coord = sum_diff_vector(x_coord, mult_vector(y, camera->up_vector), SUM);
	v = sum_diff_vector(xy_coord, camera->coordinates, DIFF);
	v = normalize_vector(v);
	return (v);
}

void	init_point_data(t_color_finder *data, t_scene *scene, int x, int y)
{
	data->color = make_color_trgb(BACKGROUND_COLOR);
	data->saw_nothing = TRUE;
	data->line_vector = calculate_pixel_vector(scene->camera, x, y);
	data->checking_light = FALSE;
}

int	find_color(t_scene *scene, int x, int y)
{
	t_color_finder	data;

	x -= X_RES / 2;
	y = -y + Y_RES / 2;
	init_point_data(&data, scene, x, y);
	find_point_seen(scene, &data);
	data.checking_light = TRUE;
	calculate_color(scene, &data);
	return (create_trgb(0, data.color.red, data.color.green, data.color.blue));
}

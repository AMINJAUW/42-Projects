/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_point_seen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:06:59 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/23 11:43:49 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	find_point_seen(t_scene *scene, t_color_finder *data)
{
	double	t_value;
	t_list	*checking;

	t_value = -1;
	checking = scene->spheres;
	data->origin = scene->camera->coordinates;
	while (checking != NULL)
	{
		check_sphere((t_sphere *)checking->content, data, &t_value);
		checking = checking->next;
	}
	checking = scene->planes;
	while (checking != NULL)
	{
		check_plane((t_plane *)checking->content, data, &t_value);
		checking = checking->next;
	}
	checking = scene->cylinders;
	while (checking != NULL)
	{
		check_cylinder((t_cylinder *)checking->content, data, &t_value);
		checking = checking->next;
	}
	if (t_value != -1)
		data->saw_nothing = FALSE;
}

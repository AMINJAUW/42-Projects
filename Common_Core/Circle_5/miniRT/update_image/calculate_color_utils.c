/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_color_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:29:09 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/08 11:59:13 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	has_light(t_scene *scene, t_color_finder *data)
{
	t_list	*check;

	if (scene->spot_lighting->intersect_object == TRUE
		|| data->saw_nothing == TRUE)
		return (FALSE);
	check = scene->cylinders;
	while (check != NULL)
	{
		if (((t_cylinder *)check->content)->camera_inside
			!= ((t_cylinder *)check->content)->with_light_inside)
			return (FALSE);
		check = check->next;
	}
	check = scene->spheres;
	while (check != NULL)
	{
		if (((t_sphere *)check->content)->camera_inside
			!= ((t_sphere *)check->content)->with_light_inside)
			return (FALSE);
		check = check->next;
	}
	return (TRUE);
}

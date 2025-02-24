/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_image_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:25:29 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/25 14:01:10 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	update_cylinders(t_scene *scene)
{
	t_list		*cylinders;
	t_cylinder	*cyl;

	cylinders = scene->cylinders;
	while (cylinders != NULL)
	{
		cyl = (t_cylinder *)cylinders->content;
		cyl->bottom_center = sum_diff_vector(cyl->coordinates, mult_vector((-1.0
						* cyl->height) / 2.0, cyl->vector), SUM);
		cylinders = cylinders->next;
	}
}

void	check_light_inside_cyl(t_scene *scene, t_list *check)
{
	check = scene->cylinders;
	while (check != NULL && scene->spot_lighting->intersect_object == FALSE)
	{
		if (is_on_cyl(scene->spot_lighting->coordinates,
				(t_cylinder *)check->content))
			scene->spot_lighting->intersect_object = TRUE;
		check = check->next;
	}
}

void	check_light_inside_object(t_scene *scene)
{
	t_list	*check;

	scene->spot_lighting->intersect_object = FALSE;
	check = scene->spheres;
	while (check != NULL && scene->spot_lighting->intersect_object == FALSE)
	{
		if (squared_norm(sum_diff_vector(scene->spot_lighting->coordinates,
					((t_sphere *)check->content)->coordinates, DIFF)) == 
			pow(((t_sphere *)check->content)->diameter / 2, 2))
			scene->spot_lighting->intersect_object = TRUE;
		check = check->next;
	}
	check = scene->planes;
	while (check != NULL && scene->spot_lighting->intersect_object == FALSE)
	{
		if (dot_poduct(((t_plane *)check->content)->vector,
				sum_diff_vector(scene->spot_lighting->coordinates,
					((t_plane *)check->content)->coordinates, DIFF)) == 0)
			scene->spot_lighting->intersect_object = TRUE;
		check = check->next;
	}
	check_light_inside_cyl(scene, check);
}

void	check_camera_inside_object(t_scene *scene)
{
	t_list	*check;

	check = scene->spheres;
	while (check != NULL)
	{
		((t_sphere *)check->content)->camera_inside = -1;
		if (squared_norm(sum_diff_vector(scene->camera->coordinates,
					((t_sphere *)check->content)->coordinates,
					DIFF)) <= pow(((t_sphere *)check->content)->diameter / 2,
				2))
			((t_sphere *)check->content)->camera_inside = TRUE;
		check = check->next;
	}
	check = scene->cylinders;
	while (check != NULL)
	{
		((t_cylinder *)check->content)->camera_inside = -1;
		if (inside_cyl(scene->camera->coordinates,
				(t_cylinder *)check->content))
			((t_cylinder *)check->content)->camera_inside = TRUE;
		check = check->next;
	}
}

void	check_spot(t_scene *scene)
{
	t_list	*check;

	check = scene->spheres;
	while (check != NULL)
	{
		((t_sphere *)check->content)->with_light_inside = -1;
		if (squared_norm(sum_diff_vector(scene->spot_lighting->coordinates,
					((t_sphere *)check->content)->coordinates,
					DIFF)) <= pow(((t_sphere *)check->content)->diameter / 2,
				2))
			((t_sphere *)check->content)->with_light_inside = TRUE;
		check = check->next;
	}
	check = scene->cylinders;
	while (check != NULL)
	{
		((t_cylinder *)check->content)->with_light_inside = -1;
		if (inside_cyl(scene->spot_lighting->coordinates,
				(t_cylinder *)check->content))
			((t_cylinder *)check->content)->with_light_inside = TRUE;
		check = check->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:32 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/19 15:09:11 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	clear_scene(t_scene *scene)
{
	if (scene != NULL)
	{
		if (scene->camera != NULL)
			free(scene->camera);
		if (scene->ambient_lighting != NULL)
			free(scene->ambient_lighting);
		if (scene->spot_lighting != NULL)
			free(scene->spot_lighting);
		ft_lstclear(&scene->spheres, free);
		ft_lstclear(&scene->planes, free);
		ft_lstclear(&scene->cylinders, free);
	}
}

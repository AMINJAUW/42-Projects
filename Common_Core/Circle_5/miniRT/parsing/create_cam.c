/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:32:57 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 13:48:46 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	verify_cam(char *line, t_scene *scene)
{
	(void) scene;
	line += ft_next_char(line, 'C') + 1;
	line = is_coordinates(line);
	if (line == NULL || *line == 0 || ft_in_set_char(*(line++), " \t") == FALSE)
		return (print_error(CAMERA_FORMAT));
	line = is_vector(line);
	if (line == NULL || *line == 0 || ft_in_set_char(*(line++), " \t") == FALSE)
		return (print_error(CAMERA_FORMAT));
	line = is_whole_number_range(line, 1, 179);
	if (line == NULL)
		return (print_error(CAMERA_FORMAT));
	while (ft_in_set_char(*line, " \t") == TRUE)
		line++;
	if (*line != 0 && *line != '\n')
		return (print_error(CAMERA_FORMAT));
	return (SUCCES);
}

int	create_cam(char *line, t_scene *scene)
{
	scene->camera = (t_camera *)ft_calloc(1, sizeof(t_camera));
	if (scene->camera == NULL)
		return (FAIL);
	line += ft_next_char(line, 'C') + 1;
	line += add_coordinates(line, &scene->camera->coordinates);
	line += add_norm_vector(line, &scene->camera->vector);
	scene->camera->fov = ft_atoi(line);
	return (SUCCES);
}

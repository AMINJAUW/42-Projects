/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:33:01 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 13:49:13 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	verify_plane(char *line, t_scene *scene)
{
	(void) scene;
	line += ft_next_char(line, 'p') + 2;
	line = is_coordinates(line);
	if (line == NULL || *line == 0 || ft_in_set_char(*(line++), " \t") == FALSE)
		return (print_error(PLANE_FORMAT));
	line = is_vector(line);
	if (line == NULL || *line == 0 || ft_in_set_char(*(line++), " \t") == FALSE)
		return (print_error(PLANE_FORMAT));
	line = is_color(line);
	if (line == NULL)
		return (print_error(PLANE_FORMAT));
	while (ft_in_set_char(*line, " \t") == TRUE)
		line++;
	if (*line != 0 && *line != '\n')
		return (print_error(PLANE_FORMAT));
	return (SUCCES);
}

int	create_plane(char *line, t_scene *scene)
{
	t_plane	*plane;
	t_list	*new;

	plane = (t_plane *)ft_calloc(1, sizeof(t_plane));
	if (plane == NULL)
		return (FAIL);
	new = ft_lstnew((void *)plane);
	if (new == NULL)
	{
		free(plane);
		return (FAIL);
	}
	ft_lstadd_back(&scene->planes, new);
	line += ft_next_char(line, 's') + 2;
	line += add_coordinates(line, &plane->coordinates);
	line += add_norm_vector(line, &plane->vector);
	line += add_color(line, &plane->color);
	return (SUCCES);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:33:00 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 13:49:59 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	verify_sphere(char *line, t_scene *scene)
{
	(void) scene;
	line += ft_next_char(line, 's') + 2;
	line = is_coordinates(line);
	if (line == NULL || *line == 0 || ft_in_set_char(*(line++), " \t") == FALSE 
		|| ft_atof(line) < 0)
		return (print_error(SPHERE_FORMAT));
	line = is_fractional(line);
	if (line == NULL || *line == 0 || ft_in_set_char(*(line++), " \t") == FALSE)
		return (print_error(SPHERE_FORMAT));
	line = is_color(line);
	if (line == NULL)
		return (print_error(SPHERE_FORMAT));
	while (ft_in_set_char(*line, " \t") == TRUE)
		line++;
	if (*line != 0 && *line != '\n')
		return (print_error(SPHERE_FORMAT));
	return (SUCCES);
}

int	create_sphere(char *line, t_scene *scene)
{
	t_sphere	*sphere;
	t_list		*new;

	sphere = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	if (sphere == NULL)
		return (FAIL);
	new = ft_lstnew((void *)sphere);
	if (new == NULL)
	{
		free(sphere);
		return (FAIL);
	}
	ft_lstadd_back(&scene->spheres, new);
	line += ft_next_char(line, 's') + 2;
	line += add_coordinates(line, &sphere->coordinates);
	sphere->diameter = ft_atof(line);
	line += ft_skip_nbrs(line);
	line += add_color(line, &sphere->color);
	return (SUCCES);
}

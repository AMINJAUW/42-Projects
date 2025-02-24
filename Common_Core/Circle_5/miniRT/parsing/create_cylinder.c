/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:33:02 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 13:45:45 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	verify_cylinder(char *line, t_scene *scene)
{
	(void) scene;
	line += ft_next_char(line, 'c') + 2;
	line = is_coordinates(line);
	if (line == NULL || *line == 0 || ft_in_set_char(*(line++), " \t") == FALSE)
		return (print_error(CYLINDER_FORMAT));
	line = is_vector(line);
	if (line == NULL || *line == 0 || ft_in_set_char(*(line++), " \t") == FALSE
		|| ft_atof(line) < 0)
		return (print_error(CYLINDER_FORMAT));
	line = is_fractional(line);
	if (line == NULL || *line == 0 || ft_in_set_char(*(line++), " \t") == FALSE
		|| ft_atof(line) < 0)
		return (print_error(CYLINDER_FORMAT));
	line = is_fractional(line);
	if (line == NULL || *line == 0 || ft_in_set_char(*(line++), " \t") == FALSE)
		return (print_error(CYLINDER_FORMAT));
	line = is_color(line);
	if (line == NULL)
		return (print_error(CYLINDER_FORMAT));
	while (ft_in_set_char(*line, " \t") == TRUE)
		line++;
	if (*line != 0 && *line != '\n')
		return (print_error(CYLINDER_FORMAT));
	return (SUCCES);
}

int	create_cylinder(char *line, t_scene *scene)
{
	t_cylinder	*cylinder;
	t_list		*new;

	cylinder = (t_cylinder *)ft_calloc(1, sizeof(t_cylinder));
	if (cylinder == NULL)
		return (FAIL);
	new = ft_lstnew((void *)cylinder);
	if (new == NULL)
	{
		free(cylinder);
		return (FAIL);
	}
	ft_lstadd_back(&scene->cylinders, new);
	line += ft_next_char(line, 'c') + 2;
	line += add_coordinates(line, &cylinder->coordinates);
	line += add_norm_vector(line, &cylinder->vector);
	cylinder->diameter = ft_atof(line);
	line += ft_skip_nbrs(line);
	cylinder->height = ft_atof(line);
	line += ft_skip_nbrs(line);
	line += add_color(line, &cylinder->color);
	return (SUCCES);
}

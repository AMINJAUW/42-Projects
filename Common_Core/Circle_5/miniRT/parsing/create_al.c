/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_al.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:32:58 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 13:47:56 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	verify_al(char *line, t_scene *scene)
{
	(void) scene;
	line += ft_next_char(line, 'A') + 1;
	line = is_fract_range(line, 0, 1);
	if (line == NULL || *line == 0 || ft_in_set_char(*(line++), " \t") == FALSE)
		return (print_error(AMBIENT_LIGHTING_FORMAT));
	line = is_color(line);
	if (line == NULL)
		return (print_error(AMBIENT_LIGHTING_FORMAT));
	while (ft_in_set_char(*line, " \t") == TRUE)
		line++;
	if (*line != 0 && *line != '\n')
		return (print_error(AMBIENT_LIGHTING_FORMAT));
	return (SUCCES);
}

int	create_al(char *line, t_scene *scene)
{
	scene->ambient_lighting
		= (t_ambient_lighting *)ft_calloc(1, sizeof(t_ambient_lighting));
	if (scene->ambient_lighting == NULL)
		return (FAIL);
	line += ft_next_char(line, 'A') + 1;
	scene->ambient_lighting->ratio = ft_atof(line);
	line += ft_skip_nbrs(line);
	line += add_color(line, &scene->ambient_lighting->color);
	return (SUCCES);
}

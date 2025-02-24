/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:32:59 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 13:49:32 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	verify_sl(char *line, t_scene *scene)
{
	(void) scene;
	line += ft_next_char(line, 'L') + 1;
	line = is_coordinates(line);
	if (line == NULL || *line == 0 || ft_in_set_char(*(line++), " \t") == FALSE)
		return (print_error(SPOT_LIGHTING_FORMAT));
	line = is_fract_range(line, 0, 1);
	if (line == NULL || *line == 0 || ft_in_set_char(*(line++), " \t") == FALSE)
		return (print_error(SPOT_LIGHTING_FORMAT));
	line = is_color(line);
	if (line == NULL)
		return (print_error(SPOT_LIGHTING_FORMAT));
	while (ft_in_set_char(*line, " \t") == TRUE)
		line++;
	if (*line != 0 && *line != '\n')
		return (print_error(SPOT_LIGHTING_FORMAT));
	return (SUCCES);
}

int	create_sl(char *line, t_scene *scene)
{
	scene->spot_lighting
		= (t_spot_lighting *)ft_calloc(1, sizeof(t_spot_lighting));
	if (scene->spot_lighting == NULL)
		return (FAIL);
	line += ft_next_char(line, 'L') + 1;
	line += add_coordinates(line, &scene->spot_lighting->coordinates);
	scene->spot_lighting->brightness = ft_atof(line);
	line += ft_skip_nbrs(line);
	line += add_color(line, &scene->spot_lighting->color);
	return (SUCCES);
}

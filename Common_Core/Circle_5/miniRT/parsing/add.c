/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:59:35 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/16 12:36:50 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	add_coordinates(char *line, t_coordinates *coordinates)
{
	int	skipped;

	skipped = 0;
	coordinates->x = ft_atof(&line[skipped]);
	skipped += ft_next_char(&line[skipped], ',') + 1;
	coordinates->y = ft_atof(&line[skipped]);
	skipped += ft_next_char(&line[skipped], ',') + 1;
	coordinates->z = ft_atof(&line[skipped]);
	skipped += ft_skip_nbrs(&line[skipped]);
	return (skipped);
}

int	add_norm_vector(char *line, t_coordinates *vector)
{
	int	skipped;

	skipped = add_coordinates(line, vector);
	*vector = normalize_vector(*vector);
	return (skipped);
}

int	add_color(char *line, t_color *color)
{
	int	skipped;

	skipped = 0;
	color->red = ft_atoi(&line[skipped]);
	skipped += ft_next_char(&line[skipped], ',') + 1;
	color->green = ft_atoi(&line[skipped]);
	skipped += ft_next_char(&line[skipped], ',') + 1;
	color->blue = ft_atoi(&line[skipped]);
	skipped += ft_skip_nbrs(&line[skipped]);
	return (skipped);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:01:15 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/19 09:39:56 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	resize_diameter(t_mlx *mlx, int sign)
{
	double	*diameter;

	diameter = NULL;
	if (mlx->current_type == SPHERE)
		diameter = &((t_sphere *)((t_list *)mlx->current_object)->content)
			->diameter;
	if (mlx->current_type == CYLINDER)
		diameter = &((t_cylinder *)((t_list *)mlx->current_object)->content)
			->diameter;
	if (diameter != NULL && (*diameter > 1 || sign == SUM))
		*diameter += RESIZE_FACTOR * sign;
}

void	resize_height(t_mlx *mlx, int sign)
{
	double	*height;

	height = NULL;
	if (mlx->current_type == CYLINDER)
		height = &((t_cylinder *)((t_list *)mlx->current_object)->content)
			->height;
	if (height != NULL && (*height > 1 || sign == SUM))
		*height += RESIZE_FACTOR * sign;
}

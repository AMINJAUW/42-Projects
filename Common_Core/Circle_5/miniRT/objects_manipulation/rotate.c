/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:07:35 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/23 16:37:40 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rotate_x(t_mlx *mlx, int sign)
{
	if (mlx->current_type == CAMERA)
		roll((t_camera *)mlx->current_object,
			M_PI / ROTATE_FACTOR * sign, 'X');
	if (mlx->current_type == CYLINDER)
		rotation_x(&((t_cylinder *)((t_list *)mlx->current_object)
				->content)->vector, M_PI / ROTATE_FACTOR * sign);
	if (mlx->current_type == PLANE)
		rotation_x(&((t_plane *)((t_list *)mlx->current_object)
				->content)->vector, M_PI / ROTATE_FACTOR * sign);
}

void	rotate_y(t_mlx *mlx, int sign)
{
	if (mlx->current_type == CAMERA)
		roll((t_camera *)mlx->current_object,
			M_PI / ROTATE_FACTOR * sign, 'Y');
	if (mlx->current_type == CYLINDER)
		rotation_y(&((t_cylinder *)((t_list *)mlx->current_object)
				->content)->vector, M_PI / ROTATE_FACTOR * sign);
	if (mlx->current_type == PLANE)
		rotation_y(&((t_plane *)((t_list *)mlx->current_object)
				->content)->vector, M_PI / ROTATE_FACTOR * sign);
}

void	rotate_z(t_mlx *mlx, int sign)
{
	if (mlx->current_type == CAMERA)
		roll((t_camera *)mlx->current_object,
			M_PI / ROTATE_FACTOR * sign, 'Z');
	if (mlx->current_type == CYLINDER)
		rotation_z(&((t_cylinder *)((t_list *)mlx->current_object)
				->content)->vector, M_PI / ROTATE_FACTOR * sign);
	if (mlx->current_type == PLANE)
		rotation_z(&((t_plane *)((t_list *)mlx->current_object)
				->content)->vector, M_PI / ROTATE_FACTOR * sign);
}

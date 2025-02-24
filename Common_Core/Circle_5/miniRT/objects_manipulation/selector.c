/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:23:52 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/19 11:43:58 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	next_object_first_jump(t_mlx *mlx, int type)
{
	if (type == CAMERA)
	{
		mlx->current_object = mlx->scene->spot_lighting;
		mlx->current_type = SPOT_LIGHTING;
	}
	if (type == SPOT_LIGHTING)
	{
		mlx->current_object = mlx->scene->spheres;
		mlx->current_type = SPHERE;
	}
	if (type == SPHERE)
		mlx->current_object = ((t_list *)mlx->current_object)->next;
	if (type == PLANE)
		mlx->current_object = ((t_list *)mlx->current_object)->next;
	if (type == CYLINDER)
		mlx->current_object = ((t_list *)mlx->current_object)->next;
}

static void	next_object_loop_jump(t_mlx *mlx)
{
	if (mlx->current_type == SPOT_LIGHTING)
	{
		mlx->current_object = mlx->scene->spheres;
		mlx->current_type = SPHERE;
	}
	else if (mlx->current_type == SPHERE)
	{
		mlx->current_object = mlx->scene->planes;
		mlx->current_type = PLANE;
	}
	else if (mlx->current_type == PLANE)
	{
		mlx->current_object = mlx->scene->cylinders;
		mlx->current_type = CYLINDER;
	}
	else if (mlx->current_type == CYLINDER)
	{
		mlx->current_object = mlx->scene->camera;
		mlx->current_type = CAMERA;
	}
}

void	select_object(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_C)
	{
		mlx->current_object = mlx->scene->camera;
		mlx->current_type = CAMERA;
	}
	else
	{
		next_object_first_jump(mlx, mlx->current_type);
		while (mlx->current_object == NULL)
			next_object_loop_jump(mlx);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	display_infos(mlx);
}

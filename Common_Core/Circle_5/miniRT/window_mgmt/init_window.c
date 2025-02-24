/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:42:57 by vvalet            #+#    #+#             */
/*   Updated: 2023/11/08 11:58:59 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	update_camera(t_camera *camera)
{
	t_coordinates	z_axis;
	double			half_for_rad;

	z_axis.x = 0;
	z_axis.y = 0;
	z_axis.z = 1;
	if (camera->vector.z == 1 || camera->vector.z == -1)
	{
		z_axis.x++;
		z_axis.z--;
	}
	camera->right_vector = normalize_vector(
			cross_product(camera->vector, z_axis));
	camera->up_vector = normalize_vector(
			cross_product(camera->right_vector, camera->vector));
	half_for_rad = camera->fov * M_PI / 360.0;
	camera->screen_distance = X_RES / (2 * tan(half_for_rad));
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	mclose(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	errno = 0;
	clear_scene(mlx->scene);
	exit(0);
	return (0);
}

void	init_window(t_mlx *mlx)
{
	mlx->current_object = mlx->scene->camera;
	mlx->current_type = CAMERA;
	mlx->show_infos = TRUE;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, X_RES, Y_RES, "miniRT");
	mlx->img = mlx_new_image(mlx->mlx, X_RES, Y_RES);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	update_camera(mlx->scene->camera);
	update_image(mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, &mclose, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, 0, &key_hooks, mlx);
	mlx_loop(mlx->mlx);
}

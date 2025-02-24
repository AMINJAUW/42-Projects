/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:38:12 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/25 14:18:45 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	update_object_data(t_scene *scene)
{
	update_cylinders(scene);
	check_camera_inside_object(scene);
	if (scene->spot_lighting != NULL)
	{
		check_light_inside_object(scene);
		check_spot(scene);
	}
}

void	update_image(t_mlx *mlx)
{
	int	x;
	int	y;

	update_object_data(mlx->scene);
	y = 0;
	while (y < Y_RES)
	{
		x = 0;
		while (x < X_RES)
		{
			my_mlx_pixel_put(mlx, x, y, find_color(mlx->scene, x, y));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	display_infos(mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:16:38 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/21 17:49:49 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	get_opposite_color(int color, int do_it)
{
	int	num;

	if (!do_it)
		return (color);
	num = ((color >> 24) << 24);
	num += ((255 - get_r(color)) << 16)
		+ ((255 - get_g(color)) << 8) + (255 - get_b(color));
	return (num);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*((unsigned int *)dst) = color;
}

int	update_img(t_info *info)
{
	t_complex	z;
	int			x;
	int			y;

	y = 0;
	while (y < Y_RES)
	{
		x = 0;
		z.im = (y - Y_RES / 2) * info->scale;
		while (x < X_RES)
		{
			z.re = (x - X_RES / 2) * info->scale;
			if (info->mandel)
				my_mlx_pixel_put(info->mlx, x, y,
					getfractalcolor(is_mandelbrot(z), info->r, info->sat));
			else
				my_mlx_pixel_put(info->mlx, x, y,
					getfractalcolor(is_julia(z, info->c), info->r, info->sat));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx->mlx, info->mlx->win,
		info->mlx->img, 0, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:55:38 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/24 18:05:32 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	scroll(int button, int x, int y, t_info *info)
{
	if (x < 0 || x > X_RES || y < 0 || y > Y_RES)
		return (0);
	if (button == MOUSE_SCROLL_UP)
	{
		info->scale /= 2.0;
		ft_printf("\x1b[38;5;12mnew Scale = \x1b[31m%i.%i\x1b[0m\n\r",
			(int)(info->scale * 50000), (int)(info->scale * 50000000) % 1000);
		ft_printf("\x1b[33mupdating image please wait\x1b[0m\r");
		update_img(info);
		ft_printf("\x1b[32mDone1%s\x1b[0m\r", SP);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		info->scale *= 2.0;
		ft_printf("\x1b[38;5;12mnew Scale = \x1b[31m%i.%i\x1b[0m\n\r",
			(int)(info->scale * 50000), (int)(info->scale * 50000000) % 1000);
		ft_printf("\x1b[33mupdating image please wait\x1b[0m\r");
		update_img(info);
		ft_printf("\x1b[32mDone2%s\x1b[0m\r", SP);
	}
	return (0);
}

int	update_julia(int keycode, t_info *info)
{
	if (info->julia && (keycode == KEY_W || keycode == KEY_UP
			|| keycode == KEY_S || keycode == KEY_DOWN || keycode == KEY_A
			|| keycode == KEY_LEFT || keycode == KEY_D || keycode == KEY_RIGHT))
	{
		ft_printf("\x1b[33mCalculating image%s\x1b[0m\r", SP);
		update_img(info);
		ft_printf("\x1b[32mUpdated !%s\x1b[0m\n", SP);
	}
	return (0);
}

int	key_push(int keycode, t_info *info)
{
	if (!other_keys(keycode, info))
		return (0);
	if (info->julia)
	{
		if (keycode == KEY_W || keycode == KEY_UP || keycode == KEY_S
			|| keycode == KEY_DOWN)
			info->c.im += info->change * (1 - 2 * (keycode == KEY_S
						|| keycode == KEY_DOWN));
		else if (keycode == KEY_A || keycode == KEY_LEFT || keycode == KEY_D
			|| keycode == KEY_RIGHT)
			info->c.re += info->change * (1 - 2 * (keycode == KEY_A
						|| keycode == KEY_LEFT));
		else
			return (0);
		ft_printf("new value of c = %c%d.%03d %c %d.%03di\n",
			'-' * is_neg(info->c.re),
			(1 - 2 * is_neg(info->c.re)) * (int)info->c.re,
			((1 - 2 * is_neg(info->c.re)) * (int)(info->c.re * 1000)
				% 1000),
			'-' * is_neg(info->c.im) + '+' * !is_neg(info->c.im),
			(1 - 2 * is_neg(info->c.im)) * (int)info->c.im,
			((1 - 2 * is_neg(info->c.im)) * (int)(info->c.im * 1000)
				% 1000));
	}
	return (0);
}

int	mclose(t_data *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
	return (0);
}

void	init(t_info *info)
{
	t_data	mlx;

	info->mlx = &mlx;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, X_RES, Y_RES, "Fractals !");
	mlx.img = mlx_new_image(mlx.mlx, X_RES, Y_RES);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length,
			&mlx.endian);
	update_img(info);
	mlx_hook(mlx.win, ON_KEYDOWN, 0, &key_push, info);
	mlx_hook(mlx.win, ON_KEYUP, 0, &update_julia, info);
	mlx_hook(mlx.win, ON_DESTROY, 0, &mclose, &mlx);
	mlx_hook(mlx.win, ON_MOUSEDOWN, 0, &scroll, info);
	mlx_loop(mlx.mlx);
}

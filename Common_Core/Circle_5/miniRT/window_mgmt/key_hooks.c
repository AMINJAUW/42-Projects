/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:19:13 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/24 09:34:13 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	translate_hooks(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
		translate(mlx, SUM, 'X');
	else if (keycode == KEY_S)
		translate(mlx, DIFF, 'X');
	else if (keycode == KEY_D)
		translate(mlx, SUM, 'Y');
	else if (keycode == KEY_A)
		translate(mlx, DIFF, 'Y');
	else if (keycode == KEY_Q)
		translate(mlx, SUM, 'Z');
	else if (keycode == KEY_E)
		translate(mlx, DIFF, 'Z');
	update_image(mlx);
}

void	rotate_hooks(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_LEFT)
		rotate_z(mlx, SUM);
	else if (keycode == KEY_RIGHT)
		rotate_z(mlx, DIFF);
	else if (keycode == KEY_DOWN)
		rotate_y(mlx, SUM);
	else if (keycode == KEY_UP)
		rotate_y(mlx, DIFF);
	else if (keycode == KEY_PUP)
		rotate_x(mlx, SUM);
	else if (keycode == KEY_PDOWN)
		rotate_x(mlx, DIFF);
	if (mlx->current_type == CAMERA || mlx->current_type == CYLINDER
		|| mlx->current_type == PLANE)
		update_image(mlx);
}

void	resize_hooks(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_NUM_PLUS)
		resize_diameter(mlx, SUM);
	else if (keycode == KEY_NUM_MIN)
		resize_diameter(mlx, DIFF);
	else if (keycode == KEY_NUM_STAR)
		resize_height(mlx, SUM);
	else if (keycode == KEY_NUM_SLASH)
		resize_height(mlx, DIFF);
	if (mlx->current_type == SPHERE || mlx->current_type == CYLINDER)
		update_image(mlx);
}

void	show_hide_infos(t_mlx *mlx)
{
	mlx->show_infos = (mlx->show_infos == FALSE);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	if (mlx->show_infos == TRUE)
		display_infos(mlx);
}

int	key_hooks(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		mclose(mlx);
	else if (keycode == KEY_TAB || keycode == KEY_C)
		select_object(keycode, mlx);
	else if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
		|| keycode == KEY_D || keycode == KEY_E || keycode == KEY_Q)
		translate_hooks(keycode, mlx);
	else if (keycode == KEY_RIGHT || keycode == KEY_LEFT || keycode == KEY_UP
		|| keycode == KEY_DOWN || keycode == KEY_PUP || keycode == KEY_PDOWN)
		rotate_hooks(keycode, mlx);
	else if (keycode == KEY_NUM_PLUS || keycode == KEY_NUM_MIN
		|| keycode == KEY_NUM_STAR || keycode == KEY_NUM_SLASH)
		resize_hooks(keycode, mlx);
	if (keycode == KEY_I)
		show_hide_infos(mlx);
	return (0);
}

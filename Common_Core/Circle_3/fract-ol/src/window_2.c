/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:50:37 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/25 11:18:04 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	other_keys(int keycode, t_info *info)
{
	if (keycode == KEY_ESC)
	{
		exit(mlx_destroy_window(info->mlx->mlx, info->mlx->win));
	}
	else if (keycode == KEY_R)
	{
		ft_printf("\x1b[33mRefreching image please wait\r\x1b[0m");
		update_img(info);
		return (0);
	}
	else if (keycode == KEY_Q)
	{
		ft_printf("\x1b[33mChanging Colors\r\x1b[0m");
		info->sat = (info->sat < 1);
		update_img(info);
		return (0);
	}
	return (1);
}

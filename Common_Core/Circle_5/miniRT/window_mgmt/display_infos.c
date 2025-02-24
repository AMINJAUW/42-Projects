/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:52:56 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 10:38:46 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	display_coord(t_mlx *mlx, t_coordinates coord)
{
	char			buffer[400];

	ft_ftoa(coord.x, buffer);
	mlx_string_put(mlx->mlx, mlx->win, X_RES - 220, 80, TEXT_COLOR, "x =");
	mlx_string_put(mlx->mlx, mlx->win, X_RES - 180, 80, TEXT_COLOR, buffer);
	ft_ftoa(coord.y, buffer);
	mlx_string_put(mlx->mlx, mlx->win, X_RES - 220, 100, TEXT_COLOR, "y =");
	mlx_string_put(mlx->mlx, mlx->win, X_RES - 180, 100, TEXT_COLOR, buffer);
	ft_ftoa(coord.z, buffer);
	mlx_string_put(mlx->mlx, mlx->win, X_RES - 220, 120, TEXT_COLOR, "z =");
	mlx_string_put(mlx->mlx, mlx->win, X_RES - 180, 120, TEXT_COLOR, buffer);
}

static void	display_object(t_mlx *mlx)
{
	t_coordinates	coord;
	const char		str[6][17] = {"CAMERA", "AMBIENT LIGHTING", "SPOT LIGHTING",
		"SPHERE", "PLANE", "CYLINDER"};

	mlx_string_put(mlx->mlx, mlx->win, X_RES - 220, 20, TEXT_COLOR,
		"You now control a");
	mlx_string_put(mlx->mlx, mlx->win, X_RES - 220, 40, TEXT_COLOR,
		(char *)str[mlx->current_type]);
	mlx_string_put(mlx->mlx, mlx->win, X_RES - 220, 60, TEXT_COLOR,
		"at coordinates:");
	if (mlx->current_type == CAMERA)
		coord = ((t_camera *)mlx->current_object)->coordinates;
	if (mlx->current_type == SPOT_LIGHTING)
		coord = ((t_spot_lighting *)mlx->current_object)->coordinates;
	if (mlx->current_type == SPHERE)
		coord = ((t_sphere *)((t_list *)mlx->current_object)->content)
			->coordinates;
	if (mlx->current_type == PLANE)
		coord = ((t_plane *)((t_list *)mlx->current_object)->content)
			->coordinates;
	if (mlx->current_type == CYLINDER)
		coord = ((t_cylinder *)((t_list *)mlx->current_object)->content)
			->coordinates;
	display_coord(mlx, coord);
}

static void	display_keys(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, 30, 20, TEXT_COLOR,
		"Select next object: Tab");
	mlx_string_put(mlx->mlx, mlx->win, 30, 40, TEXT_COLOR,
		"Select camera: C");
	mlx_string_put(mlx->mlx, mlx->win, 30, 60, TEXT_COLOR,
		"Translations: Q W E A S D");
	mlx_string_put(mlx->mlx, mlx->win, 30, 80, TEXT_COLOR,
		"Rotations: Arrows + Page_up & Page_down");
	mlx_string_put(mlx->mlx, mlx->win, 30, 100, TEXT_COLOR,
		"Resizing: + - / *");
	mlx_string_put(mlx->mlx, mlx->win, 30, 120, TEXT_COLOR,
		"Hide/Display infos: I");
}

void	display_infos(t_mlx *mlx)
{
	if (mlx->show_infos == FALSE)
		return ;
	display_keys(mlx);
	display_object(mlx);
}

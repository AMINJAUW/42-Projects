/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:47:09 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/24 12:28:12 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	translation(t_coordinates *coord, t_coordinates vector, int sign)
{
	coord->x += vector.x * sign * TRANSLATE_FACTOR;
	coord->y += vector.y * sign * TRANSLATE_FACTOR;
	coord->z += vector.z * sign * TRANSLATE_FACTOR;
}

void	translate(t_mlx *mlx, int sign, char direction)
{
	t_coordinates	vector;

	if (direction == 'X')
		vector = mlx->scene->camera->vector;
	if (direction == 'Y')
		vector = mlx->scene->camera->right_vector;
	if (direction == 'Z')
		vector = mlx->scene->camera->up_vector;
	if (mlx->current_type == CAMERA)
		translation(&((t_camera *)mlx->current_object)->coordinates,
			vector, sign);
	if (mlx->current_type == SPOT_LIGHTING)
		translation(&((t_spot_lighting *)mlx->current_object)->coordinates,
			vector, sign);
	if (mlx->current_type == SPHERE)
		translation(&((t_sphere *)((t_list *)mlx->current_object)->content)
			->coordinates, vector, sign);
	if (mlx->current_type == CYLINDER)
		translation(&((t_cylinder *)((t_list *)mlx->current_object)->content)
			->coordinates, vector, sign);
	if (mlx->current_type == PLANE)
		translation(&((t_plane *)((t_list *)mlx->current_object)->content)
			->coordinates, vector, sign);
}

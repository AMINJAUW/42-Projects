/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:09:29 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/23 16:40:49 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	rotation(t_coordinates *v, t_coordinates ref, double angle)
{
	t_coordinates	temp;
	double			cos_a;
	double			sin_a;

	temp.x = v->x;
	temp.y = v->y;
	temp.z = v->z;
	cos_a = cos(angle);
	sin_a = sin(angle);
	v->x = temp.x * cos_a + (1 - cos(angle)) * (ref.x * ref.x * temp.x + ref.x
			* ref.y * temp.y + ref.x * ref.z * temp.z) - sin_a * (ref.z * temp.y
			- ref.y * temp.z);
	v->y = temp.y * cos_a + (1 - cos(angle)) * (ref.x * ref.y * temp.x + ref.y
			* ref.y * temp.y + ref.y * ref.z * temp.z) + sin_a * (ref.z * temp.x
			- ref.x * temp.z);
	v->z = temp.z * cos_a + (1 - cos(angle)) * (ref.x * ref.z * temp.x + ref.y
			* ref.z * temp.y + ref.z * ref.z * temp.z) - sin_a * (ref.y * temp.x
			- ref.x * temp.y);
}

void	roll(t_camera *cam, double angle, char axis)
{
	if (axis == 'X')
	{
		rotation(&cam->up_vector, cam->vector, angle);
		rotation(&cam->right_vector, cam->vector, angle);
	}
	if (axis == 'Y')
	{
		rotation(&cam->vector, cam->right_vector, angle);
		rotation(&cam->up_vector, cam->right_vector, angle);
	}
	if (axis == 'Z')
	{
		rotation(&cam->vector, cam->up_vector, angle);
		rotation(&cam->right_vector, cam->up_vector, angle);
	}
}

void	rotation_x(t_coordinates *v, double angle)
{
	double	temp_y;
	double	cos_a;
	double	sin_a;

	temp_y = v->y;
	cos_a = cos(angle);
	sin_a = sin(angle);
	v->y = cos_a * v->y - sin_a * v->z;
	v->z = sin_a * temp_y + cos_a * v->z;
}

void	rotation_y(t_coordinates *v, double angle)
{
	double	temp_z;
	double	cos_a;
	double	sin_a;

	temp_z = v->z;
	cos_a = cos(angle);
	sin_a = sin(angle);
	v->z = -sin_a * v->x + cos_a * v->z;
	v->x = cos_a * v->x + sin_a * temp_z;
}

void	rotation_z(t_coordinates *v, double angle)
{
	double	temp_x;
	double	cos_a;
	double	sin_a;

	temp_x = v->x;
	cos_a = cos(angle);
	sin_a = sin(angle);
	v->x = cos_a * v->x - sin_a * v->y;
	v->y = sin_a * temp_x + cos_a * v->y;
}

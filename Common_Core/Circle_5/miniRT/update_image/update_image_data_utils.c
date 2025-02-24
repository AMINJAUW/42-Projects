/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_image_data_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:25:29 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/24 14:28:19 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_on_cyl(t_coordinates point, t_cylinder *cyl)
{
	t_coordinates	v_bot_point;
	double			h;

	v_bot_point = sum_diff_vector(point, cyl->bottom_center, DIFF);
	h = dot_poduct(v_bot_point, cyl->vector);
	if (h < 0 || h > cyl->height)
		return (FALSE);
	if (h == 0 || h == cyl->height)
	{
		if (squared_norm(sum_diff_vector(point,
					sum_diff_vector(cyl->bottom_center, mult_vector(h,
							cyl->vector), SUM), DIFF)) <= pow(cyl->diameter / 2,
				2))
			return (TRUE);
		return (FALSE);
	}
	if (squared_norm(sum_diff_vector(point, sum_diff_vector(cyl->bottom_center,
					mult_vector(h, cyl->vector), SUM),
				DIFF)) == pow(cyl->diameter / 2, 2))
		return (TRUE);
	return (FALSE);
}

int	inside_cyl(t_coordinates point, t_cylinder *cyl)
{
	t_coordinates	v_bot_point;
	double			h;

	v_bot_point = sum_diff_vector(point, cyl->bottom_center, DIFF);
	h = dot_poduct(v_bot_point, cyl->vector);
	if (h <= 0 || h >= cyl->height)
		return (FALSE);
	if (squared_norm(sum_diff_vector(point, sum_diff_vector(cyl->bottom_center,
					mult_vector(h, cyl->vector), SUM),
				DIFF)) < pow(cyl->diameter / 2, 2))
		return (TRUE);
	return (FALSE);
}

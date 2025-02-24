/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_on_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:07:27 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/08 12:00:29 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	on_sp(t_sphere *sp, t_coordinates p)
{
	t_coordinates	o_p;

	o_p = sum_diff_vector(p, sp->coordinates, DIFF);
	if (almosteq(squared_norm(o_p), pow(sp->diameter / 2, 2)))
		return (TRUE);
	return (FALSE);
}

int	on_cyl(t_cylinder *cyl, t_coordinates p)
{
	t_coordinates	o_p;
	double			h;
	t_coordinates	center_at_h;

	o_p = sum_diff_vector(p, cyl->bottom_center, DIFF);
	h = dot_poduct(cyl->vector, o_p);
	if ((!almosteq(h, 0) && !almosteq(h, cyl->height))
		&& (h < 0 || h > cyl->height))
		return (FALSE);
	center_at_h = sum_diff_vector(cyl->bottom_center, mult_vector(h,
				cyl->vector), SUM);
	o_p = sum_diff_vector(p, center_at_h, DIFF);
	if ((almosteq(h, 0) || almosteq(h, cyl->height))
		&& squared_norm(o_p) <= pow(cyl->diameter / 2, 2))
		return (TRUE);
	else if (h > 0 && h < cyl->height && almosteq(squared_norm(o_p),
			pow(cyl->diameter / 2, 2)))
		return (TRUE);
	return (FALSE);
}

int	on_pl(t_plane *pl, t_coordinates p)
{
	t_coordinates	o_p;

	o_p = sum_diff_vector(p, pl->coordinates, DIFF);
	if (almosteq(dot_poduct(o_p, pl->vector), 0))
		return (TRUE);
	return (FALSE);
}

int	on_object(t_color_finder *data, t_list *lst, int o_type)
{
	if (o_type == PLANE)
		return (on_pl((t_plane *)lst->content, data->point_seen));
	if (o_type == CYLINDER)
		return (on_cyl((t_cylinder *)lst->content, data->point_seen));
	if (o_type == SPHERE)
		return (on_sp((t_sphere *)lst->content, data->point_seen));
	return (FALSE);
}

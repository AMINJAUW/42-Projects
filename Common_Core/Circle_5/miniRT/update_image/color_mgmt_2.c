/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mgmt_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:45:31 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/23 11:47:13 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	make_color_trgb(int trgb)
{
	t_color	color;

	color.red = get_r(trgb);
	color.green = get_g(trgb);
	color.blue = get_b(trgb);
	return (color);
}

t_color	make_color(unsigned int red, unsigned int green, unsigned int blue)
{
	t_color	color;

	color.red = fmin(red, 255);
	color.green = fmin(green, 255);
	color.blue = fmin(blue, 255);
	return (color);
}

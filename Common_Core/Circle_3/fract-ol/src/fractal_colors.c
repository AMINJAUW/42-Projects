/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:40:56 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/25 11:19:55 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

/*
hsl_rgb = hue, satuartion, lightness, red, green, blue; 
*/

double	rgb_func(double *hsl_rgb, int n)
{
	double	k;
	double	a;

	a = hsl_rgb[1] * fmin(hsl_rgb[2], 1 - hsl_rgb[2]);
	k = fmod((n + (hsl_rgb[0] / (double)30)), 12.0);
	return (hsl_rgb[2] - (a * fmax(-1, fmin(fmin(k - 3, 9 - k), 1))));
}

int	calculate_rgb(double *hsl_rgb)
{
	int	rgb[3];

	rgb[0] = (int)255 * rgb_func(hsl_rgb, 0);
	rgb[1] = (int)255 * rgb_func(hsl_rgb, 8);
	rgb[2] = (int)255 * rgb_func(hsl_rgb, 4);
	return (create_trgb(0, rgb[0], rgb[1], rgb[2]));
}

int	getfractalcolor_basic(int iteration, int reverse)
{
	float	t;
	int		rgb[3];
	int		start_color;
	int		end_color;

	start_color = 0x000040;
	end_color = 0xFFFFFF;
	t = (float)iteration / MAX_ITERATION;
	rgb[0] = ((start_color >> 16) & 0xFF) * (1 - t) + ((end_color >> 16) & 0xFF)
		* t;
	rgb[1] = ((start_color >> 8) & 0xFF) * (1 - t) + ((end_color >> 8) & 0xFF)
		* t;
	rgb[2] = (start_color & 0xFF) * (1 - t) + (end_color & 0xFF) * t;
	if (iteration == -1)
		return (get_opposite_color(0x000000, reverse));
	return (get_opposite_color(((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]),
			reverse));
}

int	getfractalcolor(int iteration, int reverse, int saturation)
{
	double	hsl_rgb[6];

	if (iteration == -1)
		return (0x000000);
	else if (saturation < 0.5)
		return (getfractalcolor_basic(iteration, reverse));
	hsl_rgb[0] = fmod(pow(((double)iteration / MAX_ITERATION) * 360, 1.5), 360);
	hsl_rgb[1] = saturation;
	hsl_rgb[2] = 0.5 + 0.5 * sin(((double)iteration / MAX_ITERATION) * 0.5);
	return (get_opposite_color(calculate_rgb(hsl_rgb), reverse));
}

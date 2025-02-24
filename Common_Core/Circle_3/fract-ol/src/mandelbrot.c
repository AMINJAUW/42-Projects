/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:26:36 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/21 15:04:15 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	next_mandel(t_complex *values, int i, t_complex c)
{
	if (i == 0)
	{
		values[0].re = 0;
		values[0].im = 0;
	}
	else
		values[i] = complex_sum(z_square(values[i - 1]), c, 1);
	return ;
}

int	is_mandelbrot(t_complex c)
{
	static t_complex	values[MAX_ITERATION] = {0};
	int					i;

	i = 0;
	while (i < MAX_ITERATION)
	{
		next_mandel(values, i, c);
		if (i >= 1 && sq_complex_mod(values[i]) > 4)
			return (FALSE + i);
		else if (ft_check_duplicate(values, i + 1, i))
			return (TRUE);
		i++;
	}
	return (TRUE);
}

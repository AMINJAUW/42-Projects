/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:18:46 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/24 15:10:24 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

t_complex	z_square(t_complex z)
{
	t_complex	finale;

	finale.re = pow(z.re, 2) - pow(z.im, 2);
	finale.im = 2 * z.re * z.im;
	return (finale);
}

float	sq_complex_mod(t_complex z)
{
	return ((pow(z.re, 2) + pow(z.im, 2)));
}

int	ft_check_duplicate(t_complex *tab, int len, int i)
{
	int	j;

	j = 0;
	while (j < len)
	{
		if (i != j && tab[i].re == tab[j].re
			&& tab[i].im == tab[j].im)
			return (1);
		j++;
	}
	return (0);
}

t_complex	complex_sum(t_complex z1, t_complex z2, int sum)
{
	z1.re += z2.re * sum;
	z1.im += z2.im * sum;
	return (z1);
}

int	is_neg(float i)
{
	return ((i < 0));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:12:45 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/21 17:48:17 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	next_julia(t_complex *values, int i, t_complex z, t_complex c)
{
	if (i == 0)
	{
		values[0].re = z.re;
		values[0].im = z.im;
	}	
	else
		values[i] = complex_sum(z_square(values[i - 1]), c, 1);
	return ;
}

int	is_julia(t_complex z, t_complex c)
{
	static t_complex	values[MAX_ITERATION] = {0};
	int					i;

	i = 0;
	while (i < MAX_ITERATION)
	{
		next_julia(values, i, z, c);
		if (i >= 1 && sq_complex_mod(values[i]) > 4)
			return (FALSE + i);
		else if (ft_check_duplicate(values, i + 1, i))
			return (TRUE);
		i++;
	}
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:45:51 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/07 19:27:50 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	ft_dabs(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	almosteq(double a, double b)
{
	return (ft_dabs(a - b) < 0.000000000001);
}

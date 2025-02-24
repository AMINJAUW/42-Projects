/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:08:00 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/09 13:17:12 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		index;
	int		sign;
	size_t	nbr;

	index = 0;
	sign = 1;
	nbr = 0;
	while (str[index] == ' ' || (str[index] >= 9 && str[index] <= 13))
		index++;
	if (str[index] == '-')
		sign *= -1;
	if (str[index] == '+' || str[index] == '-')
		index++;
	while (str[index] >= '0' && str[index] <= '9')
	{
		nbr = (nbr * 10) + (str[index] - '0');
		if (nbr > __LONG_MAX__)
			return (-(sign == 1));
		index++;
	}
	return ((int)(nbr * sign));
}

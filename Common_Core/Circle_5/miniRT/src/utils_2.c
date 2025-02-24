/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:46:47 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 13:46:04 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	int_overflow(char *str)
{
	int				index;
	int				sign;
	long long int	n;

	index = 0;
	sign = 1;
	n = 0;
	while (ft_in_set_char(str[index], " \t") == TRUE 
		|| (str[index] >= 9 && str[index] <= 13))
		index++;
	if (str[index] == '-')
		sign *= -1;
	if (str[index] == '+' || str[index] == '-')
		index++;
	if (!str[index])
		return (0);
	while (str[index] >= '0' && str[index] <= '9')
	{
		n = (n * 10) + (str[index] - '0');
		if ((sign > 0 && n > INT_MAX) || (sign < 0 && n > -INT_MIN))
			return (TRUE);
		index++;
	}
	return (FALSE);
}

int	ft_next_char(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_skip_nbrs(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_in_set_char(str[i], " \t") == TRUE)
		i++;
	i += ft_next_char(&str[i], ' ');
	while (str[i] && ft_in_set_char(str[i], " \t") == TRUE)
		i++;
	return (i);
}

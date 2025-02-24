/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:18:57 by aminjauw          #+#    #+#             */
/*   Updated: 2025/02/24 16:58:36 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	chec_sign(int i, const char *str, int *sign)
{
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		return (1);
	}
	return (0);
}

int	chec_num(long num, const char *str, int i, int sign)
{
	if (sign == 1 && num > (INT_MAX - (str[i] - '0')) / 10)
		return (0);
	if (sign == -1 && num > (INT_MIN + (str[i] - '0')) / -10)
		return (0);
	return (2);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	num;

	i = 0;
	sign = 1;
	while ((str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v'))
		i ++;
	i += chec_sign(i, str, &sign);
	num = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (chec_num(num, str, i, sign) != 2)
			return (chec_num(num, str, i, sign));
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	if (str[i] != 0)
		return (0);
	return (num * sign);
}

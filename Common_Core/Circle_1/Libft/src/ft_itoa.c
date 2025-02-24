/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:04:40 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/09 12:53:35 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

static void	ft_strrev(char *str)
{
	int		length;
	int		i;
	char	temp;

	length = ft_strlen(str);
	i = 0;
	while (i < length / 2)
	{
		temp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = temp;
		i++;
	}
}

static int	ft_abs(int i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	int			is_neg;
	int			size;

	size = ft_size(n);
	is_neg = (n < 0);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < size - is_neg)
	{
		str[i] = '0' + ft_abs(n % 10);
		n /= 10;
		i ++;
	}
	if (is_neg)
	{
		str[i] = '-';
		i ++;
	}
	str[i] = 0;
	ft_strrev(str);
	return (str);
}

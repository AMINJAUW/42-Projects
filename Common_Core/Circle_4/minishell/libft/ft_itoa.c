/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:20:46 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/03 15:17:40 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		index;
	int		neg;
	char	*a;

	index = ft_nb_len(n);
	neg = 1;
	if (n < 0)
		neg *= -1;
	a = (char *)ft_calloc(1, ft_nb_len(n) + 1);
	if (!a)
		return (NULL);
	a[index] = 0;
	index--;
	while (index >= 0)
	{
		if (n < 0)
			a[index] = -(n % 10) + '0';
		else
			a[index] = (n % 10) + '0';
		n /= 10;
		index--;
	}
	if (neg < 0)
		a[0] = '-';
	return (a);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_value_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:38:30 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/09 13:18:00 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_value_fd(int n, int fd)
{
	long long int	big_pow;
	int				c;
	int				count;

	big_pow = 1;
	count = (n < 0);
	while (n / big_pow > 9 || n / big_pow < -9)
		big_pow *= 10;
	if (n < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
	}
	while (big_pow > 0)
	{
		if (n < 0)
			c = -((n % (big_pow * 10)) / big_pow) + '0';
		else
			c = ((n % (big_pow * 10)) / big_pow) + '0';
		if (write(fd, &c, 1) == -1)
			return (-1);
		big_pow /= 10;
		count++;
	}
	return (count);
}

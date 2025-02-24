/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putui_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:55:12 by vvalet            #+#    #+#             */
/*   Updated: 2023/06/06 14:12:56 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putui_fd(unsigned int n, int fd)
{
	size_t	big_pow;
	int		c;
	int		count;

	big_pow = 1;
	count = 0;
	while (n / big_pow > 9)
		big_pow *= 10;
	while (big_pow > 0)
	{
		c = ((n % (big_pow * 10)) / big_pow) + '0';
		if (write(fd, &c, 1) == -1)
			return (-1);
		big_pow /= 10;
		count++;
	}
	return (count);
}

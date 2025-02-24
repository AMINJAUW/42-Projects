/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem_hex_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:00:09 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/10 15:56:18 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putmem_hex_fd(long int n, int fd)
{
	size_t		big_pow;
	int			count;

	if (write(1, "0x", 2) == -1)
		return (-1);
	big_pow = 1;
	count = 2;
	while (n / big_pow > 15)
		big_pow *= 16;
	while (big_pow > 0)
	{
		if (write(fd, &HEX_MIN[n / big_pow], 1) == -1)
			return (-1);
		n %= big_pow;
		big_pow /= 16;
		count++;
	}
	return (count);
}

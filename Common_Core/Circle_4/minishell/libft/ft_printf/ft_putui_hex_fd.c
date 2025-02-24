/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putui_hex_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:00:59 by vvalet            #+#    #+#             */
/*   Updated: 2023/06/13 11:06:33 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putui_hex_fd(unsigned int n, int ltrs, int fd)
{
	size_t		big_pow;
	int			count;
	int			check;

	big_pow = 1;
	count = 0;
	while (n / big_pow > 15)
		big_pow *= 16;
	while (big_pow > 0)
	{
		if (ltrs == 0)
			check = write(fd, &HEX_MIN[n / big_pow], 1);
		if (ltrs == 1)
			check = write(fd, &HEX_MAJ[n / big_pow], 1);
		if (check == -1)
			return (-1);
		n %= big_pow;
		big_pow /= 16;
		count++;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:10:21 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/06 12:23:43 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *add, int c, int size)
{
	int				i;
	unsigned char	*d;

	d = add;
	i = 0;
	while (i < size)
	{
		d[i] = c;
		i ++;
	}
	return (add);
}

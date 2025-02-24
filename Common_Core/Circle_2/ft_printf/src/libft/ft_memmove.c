/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:16:41 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/06 12:42:16 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dest;
	char	*source;	

	dest = (char *)dst;
	source = (char *)src;
	if (len == 0)
		return (dst);
	if (dst > src)
	{
		i = len - 1;
		while (i + 1)
		{
			dest[i] = source[i];
			i --;
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:42:47 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/14 12:22:07 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_len;

	i = 0;
	j = 0;
	src_len = ft_strlen((char *)src);
	if (dstsize == 0)
		return (src_len);
	while (dest[i])
		i++;
	while (src[j] && (i + j) < (dstsize - 1))
	{
		dest[i + j] = src[j];
		j++;
	}
	if (j < dstsize)
		dest[i + j] = '\0';
	if (i > dstsize)
		return (src_len + dstsize);
	return (i + src_len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:32:47 by vvalet            #+#    #+#             */
/*   Updated: 2023/07/14 14:26:28 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memrcpy(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (dest);
	while (n--)
		((char *)dest)[n] = ((char *)src)[n];
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	if (!dest && !len)
		return (0);
	if (dest > src)
		dest = ft_memrcpy(dest, src, len);
	else
		dest = ft_memcpy(dest, src, len);
	return (dest);
}

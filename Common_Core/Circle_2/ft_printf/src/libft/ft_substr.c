/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:48:17 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/09 11:33:43 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	if (!s)
		return (0);
	if (ft_strlen((char *)s) <= start)
		len = 0;
	else if (len > ft_strlen((char *)s) - start)
		len = ft_strlen((char *)s) - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (0);
	i = 0;
	while (i < len && s[start + i] != 0)
	{
		sub[i] = s[start + i];
		i ++;
	}
	sub[i] = 0;
	return (sub);
}

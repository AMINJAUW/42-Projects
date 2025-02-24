/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:58:29 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/27 16:01:22 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	tot_length;
	size_t	i;
	size_t	j;

	if ((!s1 || !s2))
		return (0);
	tot_length = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = malloc(sizeof(char) * (1 + tot_length));
	if (!str)
		return (0);
	i = 0;
	while (s1[i] != 0)
	{
		str[i] = s1[i];
		i ++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		str[i + j] = s2[j];
		j ++;
	}
	str[i + j] = 0;
	return (str);
}

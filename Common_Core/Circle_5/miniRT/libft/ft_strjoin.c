/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:41:29 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/03 15:19:02 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*joined;
	size_t		size_1;
	size_t		size_2;

	if (!s1 || !s2)
		return (NULL);
	size_1 = ft_strlen(s1);
	size_2 = ft_strlen(s2);
	if (size_1 + size_2 < size_1 || size_1 + size_2 < size_2)
		return (NULL);
	joined = (char *)ft_calloc(1, size_1 + size_2 + 1);
	if (!joined)
		return (NULL);
	ft_memcpy(joined, s1, size_1);
	ft_memcpy(joined + size_1, s2, size_2 + 1);
	return (joined);
}

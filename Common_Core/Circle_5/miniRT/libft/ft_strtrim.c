/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:43:43 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/03 15:19:19 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char		*start;
	char		*end;
	char		*str;

	if (!s || !*s)
		return (ft_strdup(""));
	start = (char *)s;
	while (*start && set && in_set(*start, set))
		start++;
	end = (char *)s + ft_strlen(s) - 1;
	while (end >= s && set && in_set(*end, set))
		end--;
	if (start > end)
		return (ft_strdup(""));
	else
	{
		str = (char *)ft_calloc(1, (end - start) + 2);
		if (!str)
			return (NULL);
		ft_strlcpy(str, start, (end - start) + 2);
	}
	return (str);
}

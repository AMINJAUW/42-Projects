/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:19:55 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/03 15:46:21 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	size;

	if (!s)
		return (0);
	size = 0;
	while (s[size])
		size++;
	return (size);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen_gnl(s);
	ptr = (char *)s;
	while (ptr != (char *)s + len + 1)
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char		*joined;
	char		*ptr;
	size_t		index;
	size_t		size;

	size = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	if (size == 0)
		return (NULL);
	joined = (char *)ft_calloc(1, size + 1 * sizeof(char));
	if (!joined)
		return (NULL);
	index = 0;
	ptr = (char *)s1;
	if (!s1)
		ptr = (char *)s2;
	while (index < size)
	{
		if (*ptr == '\0')
			ptr = (char *)s2;
		joined[index] = *ptr;
		ptr++;
		index++;
	}
	joined[size] = '\0';
	return (joined);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	index;

	if (!s)
		return (NULL);
	if (start >= ft_strlen_gnl(s))
		len = 0;
	else if (len > ft_strlen_gnl(s) - start)
		len = ft_strlen_gnl(s) - start;
	substr = (char *)ft_calloc(1, len + 1);
	if (!substr)
		return (NULL);
	index = 0;
	while (index < len && s[start + index])
	{
		substr[index] = s[start + index];
		index++;
	}
	substr[index] = '\0';
	return (substr);
}

void	ft_bzero_gnl(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n--)
	{
		*ptr = 0;
		ptr++;
	}
}

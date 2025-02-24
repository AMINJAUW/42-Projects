/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:39:21 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/03 15:18:52 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	**free_ptrs(char **split, size_t i)
{
	if (i > 0)
	{
		i--;
		while (i > 0)
		{
			free(split[i]);
			i--;
		}
		free(split[i]);
	}
	free(split);
	return (NULL);
}

static char	*add_word(char *s, char c, size_t *start, size_t *end)
{
	char	*word;

	while (s[*start] && s[*start] == c)
		(*start)++;
	*end = *start;
	while (s[*end] && s[*end] != c)
		(*end)++;
	word = ft_substr(s, *start, (*end - *start));
	*start = *end;
	return (word);
}

static char	**fill_array(char *s, char c, char **split)
{
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	end = 0;
	i = 0;
	while (i < count_words(s, c))
	{
		split[i] = add_word(s, c, &start, &end);
		if (split[i] == NULL)
			return (free_ptrs(split, i));
		i++;
	}
	split[i] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (0);
	split = (char **)ft_calloc(1, (count_words(s, c) + 1) * sizeof(char *));
	if (split == NULL)
		return (0);
	split = fill_array((char *)s, c, split);
	return (split);
}

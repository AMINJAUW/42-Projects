/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:46:52 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/09 12:55:06 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char c, char charset)
{
	if (c == 0)
		return (1);
	if (charset == c)
		return (1);
	return (0);
}

static int	word_count(char *str, char charset)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (!is_sep(str[i], charset) && is_sep(str[i + 1], charset))
			counter ++;
		i ++;
	}
	return (counter);
}

static char	*nth_word(char *str, char charset, int index)
{
	int		arr[3];
	char	*word;

	arr[0] = 0;
	arr[1] = 0;
	while (arr[0] < index)
	{
		if (!is_sep(str[arr[1]], charset) && is_sep(str[arr[1] + 1], charset))
			arr[0]++;
		arr[1]++;
	}
	while (is_sep(str[arr[1]], charset))
		arr[1]++;
	arr[2] = 0;
	while (!is_sep(str[arr[1] + arr[2]], charset))
		arr[2]++;
	word = malloc(sizeof(char) * (1 + arr[2]));
	if (!word)
		return (0);
	arr[0] = -1;
	while (arr[2] - 1 > arr[0]++)
		word[arr[0]] = str[arr[1]++];
	word[arr[0]] = 0;
	return (word);
}

static char	**free_all(char **words, int index, char *str)
{
	int	i;

	i = 0;
	free(str);
	while (i < index)
	{
		free(words[i]);
		i ++;
	}
	free(words);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		i;
	char	*str;
	char	*word;

	if (!s)
		return (0);
	str = (char *)s;
	i = 0;
	words = malloc(sizeof(char *) * (word_count(str, c) + 1));
	if (!words)
		return (0);
	while (i < word_count(str, c))
	{
		word = nth_word(str, c, i);
		if (!word)
			return (free_all(words, i, word));
		words[i] = word;
		i ++;
	}
	words[i] = 0;
	return (words);
}

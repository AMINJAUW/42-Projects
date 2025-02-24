/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:27:26 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/30 14:31:57 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_words(char *av_str)
{
	int	counter;
	int	in_quotes;
	int	i;

	init_to_zero(3, &counter, &in_quotes, &i);
	while (av_str[i])
	{
		if (av_str[i] == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && !is_sep(av_str[i], ' ') && is_sep(av_str[i + 1], ' '))
			counter++;
		i++;
	}
	if (in_quotes)
		counter++;
	return (counter);
}

int	word_len(char *str)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = FALSE;
	while (str[i])
	{
		if (str[i] == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && !is_sep(str[i], ' ') && is_sep(str[i + 1], ' '))
			break ;
		i++;
	}
	return ((i + 1) * (i != 0));
}

char	*nth_word(char *str, int index)
{
	int		i;
	int		j;
	char	*word;
	int		word_length;
	int		in_quotes;

	init_to_zero(3, &j, &in_quotes, &i);
	while (j < index)
	{
		if (str[i] == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && !is_sep(str[i], ' ') && is_sep(str[i + 1], ' '))
			j++;
		i++;
	}
	while (is_sep(str[i], ' '))
		i++;
	word_length = word_len(&(str[i]));
	word = ft_calloc(sizeof(char), 1 + word_length);
	if (!init_to_zero(1, &j) && !word)
		return (0);
	while (j < word_length)
		word[j++] = str[i++];
	return (word);
}

char	**arg_split(char *av_str)
{
	char	**av;
	int		i;

	i = 0;
	if (count_char(av_str, '\'') < 2)
		return (ft_split(av_str, ' '));
	av = ft_calloc(sizeof(char *), 1 + count_words(av_str));
	if (malloc_error(av, 0))
		return (0);
	while (i < count_words(av_str))
	{
		av[i] = ft_strtrim(nth_word(av_str, i), "'");
		if (malloc_error(av[i], 1, 2, av))
			return (0);
		i++;
	}
	return (av);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:07:55 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/13 10:50:53 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_char(char *line, char *new_line,
	int *counter_l, int *counter_nl)
{
	new_line[*counter_nl] = line[*counter_l];
	(*counter_l)++;
	(*counter_nl)++;
}

static void	copy_clean_word(char *token, char *line, int pos, t_data *data)
{
	int		i;
	int		in_quotes;

	i = 0;
	in_quotes = 0;
	while (line[pos])
	{
		if (line[pos] == 0
			|| (ft_isspace(line[pos]) == TRUE && in_quotes == FALSE)
			|| ((line[pos] == '<' || line[pos] == '>' || line[pos] == '|') 
				&& in_quotes == FALSE && data->exp_tab[pos] == 0))
			break ;
		if (in_quotes == check_quotes(&line[pos], in_quotes) 
			|| data->exp_tab[pos] == 1)
			add_char(line, token, &pos, &i);
		else
		{
			in_quotes = check_quotes(&line[pos], in_quotes);
			pos++;
		}
	}
	token[i] = 0;
}

static char	*copy_clean_token(char *line, int pos, t_data *data)
{
	char	*token;

	token = (char *)ft_calloc(token_size(line, pos, data) + 1, sizeof(char));
	if (token == NULL)
		return (NULL);
	if (is_io(line, pos) == TRUE || (data->exp_tab[pos] == 0
			&& (line[pos] == '<' || line[pos] == '>' || line[pos] == '|')))
		ft_strlcpy(token, &line[pos], token_size(line, pos, data) + 1);
	else
		copy_clean_word(token, line, pos, data);
	return (token);
}

int	add_token(char *line, int i, t_data *data)
{
	char	*str;

	str = copy_clean_token(line, i, data);
	if (str == NULL)
	{
		ft_arclear(&data->lex_line);
		return (ft_error(errno, NULL, NULL, data));
	}
	if (ft_ar_addone(&data->lex_line, str) == FAIL)
	{
		free(str);
		ft_arclear(&data->lex_line);
		return (ft_error(errno, NULL, NULL, data));
	}
	free(str);
	return (SUCCES);
}

int	line_cleaner(char *line, t_data *data)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]) == TRUE)
			i++;
		else if (is_sticked_couple_quotes(line, i, data) == TRUE)
			i += 2;
		else
		{
			if (add_token(line, i, data) == FAIL)
				return (FAIL);
			i += token_size(line, i, data);
		}
	}
	return (SUCCES);
}

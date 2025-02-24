/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_line_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:07:55 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/10 10:28:23 by aminjauw         ###   ########.fr       */
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

static void	copy_clean_word(char *token, char *line, int pos, t_io *io)
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
				&& in_quotes == FALSE && io->exp_tab[pos] == 0))
			break ;
		if (in_quotes == check_quotes(&line[pos], in_quotes) 
			|| io->exp_tab[pos] == 1)
			add_char(line, token, &pos, &i);
		else
		{
			in_quotes = check_quotes(&line[pos], in_quotes);
			pos++;
		}
	}
}

static char	*copy_clean_token(char *line, int pos, t_data *data, t_io *io)
{
	char	*token;

	token = (char *)ft_calloc(io_token_size(line, pos, data) + 1, sizeof(char));
	if (token == NULL)
		return (NULL);
	if ((io->exp_tab[pos] == 0
			&& (line[pos] == '<' || line[pos] == '>' || line[pos] == '|')))
		ft_strlcpy(token, &line[pos], io_token_size(line, pos, data) + 1);
	else
		copy_clean_word(token, line, pos, io);
	return (token);
}

int	io_line_cleaner(char *line, t_data *data, t_io *io)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]) == TRUE)
		{
			i++;
			continue ;
		}
		str = copy_clean_token(line, i, data, io);
		if (str == NULL)
			return (ft_error(errno, NULL, NULL, data));
		i += io_token_size(line, i, data);
		if (ft_ar_addone(&io->split_exp_io, str) == FAIL)
		{
			free(str);
			return (ft_error(errno, NULL, NULL, data));
		}
		free(str);
	}
	return (SUCCES);
}

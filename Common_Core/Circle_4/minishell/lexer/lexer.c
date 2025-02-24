/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:40:18 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/06 12:06:13 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lex_tab_create(char *line, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (ft_strncmp(&line[i], " \"\" ", 4) == 0 
			|| ft_strncmp(&line[i], " \'\' ", 4) == 0)
			i += 4;
		else if (ft_isspace(line[i]) == TRUE)
			i++;
		else
		{
			if (data->exp_tab[i] == 0 
				&& (line[i] == '<' || line[i] == '>' || line[i] == '|'))
				data->lex_tab[j] = PUNCT;
			else
				data->lex_tab[j] = WORD;
			i += token_size(line, i, data);
			j++;
		}
	}
	return (SUCCES);
}

int	lexer(t_data *data)
{
	if (data->err_nbr != SUCCES || g_sig_flag != FALSE)
		return (SUCCES);
	data->exp_tab = (char *)ft_calloc(find_size(data->line, data) + 1,
			sizeof(char));
	if (data->exp_tab == NULL)
		return (ft_error(errno, NULL, NULL, data));
	if (env_var_exp(data) == FAIL)
		return (FAIL);
	if (line_cleaner(data->line, data) == FAIL)
		return (FAIL);
	data->lex_tab = (char *)ft_calloc(ft_arlen(data->lex_line) + 1,
			sizeof(char));
	if (data->lex_tab == NULL)
	{
		ft_arclear(&data->lex_line);
		return (ft_error(errno, NULL, NULL, data));
	}
	lex_tab_create(data->line, data);
	return (SUCCES);
}

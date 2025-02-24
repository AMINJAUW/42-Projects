/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_line_cleaner_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:14:50 by vvalet            #+#    #+#             */
/*   Updated: 2025/02/24 20:32:26 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	punct_size(char *line)
{
	if (ft_strncmp(line, ">>", 2) == 0 || ft_strncmp(line, "<<", 2) == 0)
		return (2);
	else
		return (1);
}

static int	word_size(char *line, int pos, t_data *data)
{
	int	start;
	int	in_quotes;

	start = pos;
	in_quotes = 0;
	while (1)
	{
		if (line[pos] == 0
			|| (ft_isspace(line[pos]) == TRUE && in_quotes == FALSE)
			|| ((line[pos] == '<' || line[pos] == '>' || line[pos] == '|') 
				&& in_quotes == FALSE && data->exp_tab[pos] == 0))
			break ;
		in_quotes = check_quotes(&line[pos], in_quotes);
		pos++;
	}
	return (pos - start);
}

int	io_token_size(char *line, int pos, t_data *data)
{
	if (((line[pos] == '<' || line[pos] == '>' || line[pos] == '|') 
			&&data->exp_tab[pos] == 0))
		return (punct_size(&line[pos]));
	else
		return (word_size(line, pos, data));
}

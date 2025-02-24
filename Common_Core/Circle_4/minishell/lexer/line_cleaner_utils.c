/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_cleaner_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:14:50 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/05 13:09:34 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sticked_couple_quotes(char *line, int i, t_data *data)
{
	return (ft_strncmp(&line[i], "\"\"", 2) == 0
		&& ((data->exp_tab[i + 2] == 1 || ft_isspace(line[i + 2] == FALSE))
			|| (i > 0 && (data->exp_tab[i - 1] == 1 
					|| ft_isspace(line[i - 1] == FALSE))))
		== TRUE);
}

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

int	token_size(char *line, int pos, t_data *data)
{
	if (((line[pos] == '<' || line[pos] == '>' || line[pos] == '|') 
			&& data->exp_tab[pos] == 0))
		return (punct_size(&line[pos]));
	else
		return (word_size(line, pos, data));
}

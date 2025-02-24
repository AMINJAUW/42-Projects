/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:04:16 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/10 10:29:07 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_chevrons(t_data *data, int index)
{
	size_t	len;

	len = ft_strlen(data->lex_line[index]);
	if (len > 2 || len == 0 || data->lex_tab[index] == FALSE)
		return (FALSE);
	if (len == 1)
		return ((ft_strncmp(data->lex_line[index], "<", 2)
				&& ft_strncmp(data->lex_line[index], ">", 2)) == FALSE);
	return ((ft_strncmp(data->lex_line[index], "<<", 3)
			&& ft_strncmp(data->lex_line[index], ">>", 3)) == FALSE);
}

int	is_pipe(t_data *data, int index)
{
	if (data->lex_tab[index] == FALSE)
		return (FALSE);
	return (ft_strncmp((const char *)data->lex_line[index], "|", 2) == 0);
}

int	index_of_nth_block(t_data *data, int command_block)
{
	int	i;
	int	pipe_counter;

	i = 0;
	pipe_counter = 0;
	if (command_block == 0)
		return (0);
	while (pipe_counter < command_block && data->lex_line[i])
	{
		if (is_pipe(data, i))
		{
			pipe_counter++;
			if (data->lex_line[i + 1] == NULL)
				return (i);
		}
		i++;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:31:32 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/06 13:02:09 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_param(t_data *data, int index)
{
	int	i;
	int	counter;

	i = index;
	counter = 0;
	if (*data->lex_line == NULL)
		return (-1);
	while (data->lex_line[i] != NULL && !is_pipe(data, i))
	{
		if (is_chevrons(data, i))
		{
			i++;
		}
		else
			counter++;
		i++;
	}
	return (counter);
}

int	mk_cmd_line(char **cmd_line, t_data *data, int index, int command_block)
{
	int	chevrons;
	int	nb_args;
	int	i;

	chevrons = 0;
	i = 0;
	nb_args = ft_count_param(data, index);
	while (i < nb_args)
	{
		while (is_chevrons(data, index + chevrons + i)
			&& *data->lex_line)
			chevrons += 2;
		cmd_line[i] = data->lex_line[index + chevrons + i];
		i++;
	}
	if (commands_add_back(data, cmd_line, command_block) == FAIL)
		return (FAIL);
	return (SUCCES);
}

int	clear_lst_elements_of_arr(char **arr, int i)
{
	while (arr[i] != NULL)
	{
		ft_free((void **)&arr[i]);
		i++;
	}
	return (FAIL);
}

int	to_next_block(t_data *data, int i)
{
	while (data->lex_line[i] != NULL)
	{
		if (is_pipe(data, i))
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

int	mk_commands(t_data *data)
{
	char	**cmd_line;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (data->lex_line[i] != NULL)
	{
		cmd_line = ft_calloc(ft_count_param(data, i) + 1,
				sizeof(char *));
		if (cmd_line == NULL)
		{
			clear_lst_elements_of_arr(data->lex_line, i);
			return (ft_error(errno, NULL, NULL, data));
		}
		if (mk_cmd_line(cmd_line, data, i, ++j) == FAIL)
		{
			clear_lst_elements_of_arr(data->lex_line, i);
			free(cmd_line);
			return (FAIL);
		}
		i = to_next_block(data, i);
	}
	return (SUCCES);
}

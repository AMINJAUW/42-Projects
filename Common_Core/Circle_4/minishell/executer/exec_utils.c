/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:27:23 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/04 15:43:07 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_path(t_data *data)
{
	if (data->exec_path == NULL || data->exec_path[0] == NULL)
		return (TRUE);
	return (FALSE);
}

void	exit_child_process(int exit_nbr, t_data *data)
{
	data->err_nbr = exit_nbr;
	close_env(data);
}

int	string_arr_empty(char **str)
{
	if (str == NULL || str[0] == NULL)
		return (TRUE);
	return (FALSE);
}

int	is_path_cmd(char *cmd)
{
	int	i;

	i = ft_strlen(cmd);
	while (i >= 0 && cmd[i] != '/')
		i--;
	if (i < 0)
		return (FALSE);
	return (TRUE);
}

int	no_commands(t_data *data)
{
	t_cmd	*command;

	command = data->commands;
	if (data->commands == NULL)
		return (TRUE);
	while (command != NULL)
	{
		if (command->command_line != NULL 
			&& command->command_line[0] != NULL)
			return (FALSE);
		if (command->io != NULL)
			return (FALSE);
		command = command->next;
	}
	return (TRUE);
}

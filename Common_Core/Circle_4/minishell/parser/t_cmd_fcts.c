/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:14:49 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/06 13:02:31 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	io_in_cmd_block(t_data *data, int command_block)
{
	int	i;

	i = index_of_nth_block(data, command_block);
	while (data->lex_line[i] != NULL && !is_pipe(data, i))
	{
		if (is_chevrons(data, i))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_cmd	*commands_last(t_cmd *start)
{
	while (start->next != NULL)
		start = start->next;
	return (start);
}

int	commands_add_back(t_data *data, char **command_line, int command_block)
{
	t_cmd	*chained_list;

	chained_list = ft_calloc(1, sizeof(t_cmd));
	if (!chained_list)
		return (ft_error(errno, NULL, NULL, data));
	chained_list->command_line = command_line;
	chained_list->next = NULL;
	chained_list->cmd_path = NULL;
	chained_list->io = mk_io(data, command_block);
	if (chained_list->io == NULL
		&& io_in_cmd_block(data, command_block) == TRUE)
	{
		ft_free((void **)&chained_list);
		return (FAIL);
	}
	chained_list->input_fd = STDIN_FILENO;
	chained_list->output_fd = STDOUT_FILENO;
	if (data->err_nbr != 0)
		return (FAIL);
	if (data->commands == NULL)
		data->commands = chained_list;
	else
		commands_last(data->commands)->next = chained_list;
	return (SUCCES);
}

void	commands_free_first(t_data *data)
{
	t_cmd	*new_start;

	if (data->commands == NULL)
		return ;
	new_start = data->commands->next;
	if (data->commands->command_line != NULL)
	{
		ft_arclear(&data->commands->command_line);
		if (data->commands->io != NULL)
			io_free_all(data->commands->io);
	}
	free(data->commands->cmd_path);
	free(data->commands);
	data->commands = new_start;
}

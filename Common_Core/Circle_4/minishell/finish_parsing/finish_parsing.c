/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:05:50 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/06 12:34:08 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_final_line(t_data *data, char *temp_line)
{
	ft_free((void **)&data->final_line);
	data->final_line = ft_strjoins(3, temp_line, " ", data->line);
	ft_free((void **)&temp_line);
	if (data->final_line == NULL)
		return (ft_error(errno, NULL, NULL, data));
	return (SUCCES);
}

static int	read_new_cmd(t_data *data, char *temp_line)
{
	ft_free((void **)&data->line);
	data->line = readline("\x1b[31m> \x1b[0m");
	if (data->line == NULL || g_sig_flag == SIGINT)
	{
		ft_free((void **)&temp_line);
		if (g_sig_flag == SIGINT)
		{
			data->err_nbr = 1;
			return (FAIL);
		}
		else if (errno != 0)
			return (ft_error(errno, NULL, NULL, data));
		else
			return (ft_error(258, NULL, EOF_TRAILING_PIPE, data));
	}
	return (SUCCES);
}

static int	complete_commands(t_data *data)
{
	t_cmd	*commands;
	char	*temp_line;

	while (data->trailing_pipe == TRUE)
	{
		temp_line = ft_strdup(data->final_line);
		if (temp_line == NULL)
			return (ft_error(errno, NULL, NULL, data));
		if (read_new_cmd(data, temp_line) == FAIL)
			return (FAIL);
		if (update_final_line(data, temp_line) == FAIL)
			return (FAIL);
		ft_free((void **)&data->lex_line);
		commands = (commands_last(data->commands));
		lexer(data);
		parser(data);
		commands = commands->next;
		while (data->err_nbr == SUCCES && commands != NULL)
		{
			if (complete_heredocs(commands, data) == FAIL)
				return (FAIL);
			commands = commands->next;
		}
	}
	return (SUCCES);
}

int	finish_parsing(t_data *data)
{
	t_cmd	*commands;

	if (data->err_nbr != SUCCES || g_sig_flag != FALSE)
		return (SUCCES);
	commands = data->commands;
	while (commands)
	{
		if (complete_heredocs(commands, data) == FAIL)
			return (FAIL);
		commands = commands->next;
	}
	if (data->trailing_pipe)
	{
		if (complete_commands(data) == FAIL)
			return (close_heredocs_on_failure(data, NULL));
	}
	return (SUCCES);
}

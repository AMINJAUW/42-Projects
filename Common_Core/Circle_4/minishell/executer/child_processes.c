/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:27:23 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/10 09:50:10 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_program(t_data *data, t_cmd *commands, int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(data->saved_tty_fds[0]);
	close(data->saved_tty_fds[1]);
	if (commands->command_line == NULL || commands->command_line[0] == NULL)
		exit_child_process(SUCCES, data);
	data->cur_cmd = commands->command_line[0];
	if (is_builtin(data->cur_cmd) == TRUE)
	{
		run_builtin(data, commands);
		exit_child_process(data->err_nbr, data);
	}
	if (access_command(data, commands) == FAIL)
		exit_child_process(data->err_nbr, data);
	if (execve(commands->cmd_path, commands->command_line, data->envp) == -1)
	{
		ft_error(errno, NULL, NULL, data);
		if (data->err_nbr == 2 && data->exec_path == NULL)
			exit_child_process(127, data);
		else
			exit_child_process(data->err_nbr, data);
	}
	exit_child_process(SUCCES, data);
}

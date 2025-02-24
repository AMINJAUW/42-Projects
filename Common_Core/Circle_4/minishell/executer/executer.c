/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:07:59 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/10 10:09:57 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_builtin(t_data *data)
{
	if (handle_io_files(data->commands, data))
		return (FAIL);
	fd_management_builtin(data->commands, data);
	run_builtin(data, data->commands);
	restore_tty(data);
	return (SUCCES);
}

static void	wait_child_processes(int pid, t_data *data)
{
	waitpid(pid, &data->err_nbr, 0); 
	restore_tty(data);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(data->err_nbr))
		data->err_nbr = WEXITSTATUS(data->err_nbr);
	else if (WIFSIGNALED(data->err_nbr))
	{
		if (WTERMSIG(data->err_nbr) == 2)
			data->err_nbr = 130;
		else if (WTERMSIG(data->err_nbr) == 3)
			data->err_nbr = 131;
	}
}

static int	launch_program(t_cmd *command, int pipe_fd[2], t_data *data,
			int *pid)
{
	fd_management_output(command, pipe_fd, data);
	*pid = fork();
	if (*pid == -1)
	{
		fork_error(command, pipe_fd, data);
		return (FAIL);
	}
	if (*pid == 0)
		run_program(data, command, pipe_fd);
	fd_management_input(command, pipe_fd, data);
	return (SUCCES);
}

static int	execute_commands(t_data *data)
{
	t_cmd	*command;
	int		pid;
	int		pipe_fd[2];

	command = data->commands;
	pid = 0;
	while (command)
	{
		if (pipe(pipe_fd) == -1)
		{
			ft_error(errno, NULL, NULL, data);
			restore_tty(data);
			break ;
		}
		if (handle_io_files(command, data) == FAIL)
		{
			if (io_file_error(pipe_fd) && data->err_nbr == ENOMEM)
				break ;
		}
		else if (launch_program(command, pipe_fd, data, &pid) == FAIL)
			break ;
		command = command->next;
	}
	wait_child_processes(pid, data);
	return (SUCCES);
}

int	executer(t_data *data)
{
	if (data->err_nbr != SUCCES || no_commands(data) == TRUE)
		return (SUCCES);
	if (string_arr_empty(data->commands->command_line) == FALSE
		&& is_builtin(data->commands->command_line[0]) == TRUE
		&& data->commands->next == NULL)
		return (execute_builtin(data));
	else
		return (execute_commands(data));
}

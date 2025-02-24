/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_fd_mgmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:17:41 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/04 11:21:47 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_management_output(t_cmd *command, int pipe_fd[2], t_data *data)
{
	if (command->next == NULL && command->output_fd == STDOUT_FILENO)
		command->output_fd = data->saved_tty_fds[1];
	else if (command->next != NULL && command->output_fd == STDOUT_FILENO)
		command->output_fd = pipe_fd[1];
	if (command->output_fd != STDOUT_FILENO)
		dup2(command->output_fd, STDOUT_FILENO);
	close_fd_secure(command->output_fd, data);
	close(pipe_fd[1]);
}

void	fd_management_input(t_cmd *command, int pipe_fd[2], t_data *data)
{
	dup2(pipe_fd[0], STDIN_FILENO);
	close_fd_secure(command->input_fd, data);
	close(pipe_fd[0]);
}

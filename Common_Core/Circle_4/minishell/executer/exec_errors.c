/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:13:47 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/10 10:09:04 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_error(t_cmd *command, int pipe_fd[2], t_data *data)
{
	ft_error(errno, NULL, NULL, data);
	close_fd_secure(command->input_fd, data);
	close(pipe_fd[0]);
	restore_tty(data);
}

int	io_file_error(int pipe_fd[2])
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (SUCCES);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:53:14 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/13 12:19:49 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_heredocs_on_failure(t_data *data, t_io *io)
{
	t_cmd	*cmd_ptr;
	t_io	*io_ptr;

	cmd_ptr = data->commands;
	while (cmd_ptr)
	{
		io_ptr = cmd_ptr->io;
		if (io_ptr != NULL)
		{
			if (io_ptr == io)
				return (FAIL);
			while (input_remaining(io_ptr) == TRUE)
			{
				io_ptr = io_ptr->next;
				if (io_ptr == io)
					return (FAIL);
			}
			if (io_ptr->type == HEREDOC)
				close(io_ptr->heredoc_read_end);
		}
		cmd_ptr = cmd_ptr->next;
	}
	return (FAIL);
}

static int	close_pipes_on_failure(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (FAIL);
}

static int	read_write_heredoc(t_data *data, t_io *io, int *pipe_fd)
{
	while (1)
	{
		ft_free((void **)&data->line);
		data->line = readline("\x1b[33m> \x1b[0m");
		if (data->line == NULL || g_sig_flag != 0 || (data->line != NULL
				&& ft_strncmp(data->line, (char *)io->io, ft_strlen(data->line)
					+ 1) == 0))
			break ;
		if (ft_char_count(data->line, '$') > 0
			&& env_var_exp_heredoc(data, io) == FAIL)
			return (close_pipes_on_failure(pipe_fd));
		if (write(pipe_fd[1], data->line, ft_strlen(data->line)) == -1
			|| write(pipe_fd[1], "\n", 1) == -1)
			return (ft_error(errno, NULL, NULL, data)
				|| close_pipes_on_failure(pipe_fd));
	}
	if (g_sig_flag != 0 || errno != 0)
	{
		if (g_sig_flag != 0)
			data->err_nbr = 1;
		else if (errno != 0)
			ft_error(errno, NULL, NULL, data);
		return (close_pipes_on_failure(pipe_fd));
	}
	return (SUCCES);
}

int	complete_heredocs(t_cmd *commands, t_data *data)
{
	int		pipe_fd[2];
	t_io	*io;

	io = commands->io;
	while (io != NULL)
	{
		if (io->type != HEREDOC)
		{
			io = io->next;
			continue ;
		}
		if (pipe(pipe_fd) == -1)
		{
			close_heredocs_on_failure(data, io);
			return (ft_error(errno, NULL, NULL, data));
		}
		if (read_write_heredoc(data, io, pipe_fd) == FAIL)
			return (FAIL);
		close(pipe_fd[1]);
		io->heredoc_read_end = pipe_fd[0];
		if (input_remaining(io) == TRUE)
			close(pipe_fd[0]);
		io = io->next;
	}
	return (SUCCES);
}

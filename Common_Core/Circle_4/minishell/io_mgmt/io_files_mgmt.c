/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_files_mgmt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:52:34 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/10 10:28:37 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_input_file(t_cmd *command, t_io *io, t_data *data)
{
	close_fd_secure(command->input_fd, data);
	command->input_fd = open(io->split_exp_io[0], O_RDONLY);
	if (command->input_fd == -1)
	{
		close_fd_secure(command->output_fd, data);
		if (errno == 13)
			return (ft_error(1, NULL,
					PERMISSION_STR, data));
		else if (errno == 2)
			return (ft_error(1, NULL, NO_FILE_STR, data));
		else
			return (ft_error(errno, NULL, NULL, data));
	}
	return (SUCCES);
}

static int	open_output_file(t_cmd *command, t_io *io, t_data *data)
{
	close_fd_secure(command->output_fd, data);
	command->output_fd = open(io->split_exp_io[0], io->open_mode, 0644);
	if (command->output_fd == -1)
	{
		close_fd_secure(command->input_fd, data);
		if (errno == 13)
			return (ft_error(1, NULL,
					PERMISSION_STR, data));
		else
			return (ft_error(errno, NULL, NULL, data));
	}
	return (SUCCES);
}

static int	open_io_file(t_cmd *command, t_io *io, t_data *data)
{
	if (io->type == HEREDOC)
	{
		close_fd_secure(command->input_fd, data);
		command->input_fd = io->heredoc_read_end;
	}
	else
	{
		if (io_lexer(io, data) == FAIL)
			return (FAIL);
		if (io->split_exp_io[1] != NULL)
			return (ft_error(1, NULL, AMBIGUOUS_REDIR, data));
	}
	if (io->type == INPUT_FILE)
		return (open_input_file(command, io, data));
	if (io->type == OUTPUT_FILE)
		return (open_output_file(command, io, data));
	return (SUCCES);
}

int	handle_io_files(t_cmd *command, t_data *data)
{
	t_io	*io;

	io = command->io;
	while (io)
	{
		data->cur_cmd = io->io;
		if (open_io_file(command, io, data) == FAIL)
			return (FAIL);
		if (io->type == HEREDOC || io->type == INPUT_FILE)
		{
			dup2(command->input_fd, STDIN_FILENO);
			close_fd_secure(command->input_fd, data);
		}
		io = io->next;
	}
	data->cur_cmd = command->command_line[0];
	return (SUCCES);
}

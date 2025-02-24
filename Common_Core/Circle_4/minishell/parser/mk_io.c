/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk_io.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:06:02 by aminjauw          #+#    #+#             */
/*   Updated: 2023/09/22 12:03:21 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_heredoc(t_io *io)
{
	int		i;
	int		j;
	int		in_quotes;

	i = 0;
	j = 0;
	in_quotes = 0;
	if (io->io[j] == '\0')
		return (io->io);
	while (j == 0 || io->io[j - 1] != '\0')
	{
		if (in_quotes == check_quotes(&io->io[j], in_quotes))
		{
			io->io[i] = io->io[j];
			i++;
			j++;
		}
		else
		{
			io->is_in_quotes = TRUE;
			in_quotes = check_quotes(&io->io[j], in_quotes);
			j++;
		}
	}
	return (io->io);
}

int	input_remaining(t_io *io)
{
	io = io->next;
	while (io)
	{
		if (io->type == INPUT_FILE || io->type == HEREDOC)
			return (TRUE);
		io = io->next;
	}
	return (FALSE);
}

void	fill_io_data(t_io *io, char *chevrons)
{
	if (ft_strncmp((const char *)chevrons, "<", 2) == 0)
	{
		io->type = INPUT_FILE;
		io->open_mode = O_RDONLY;
	}
	else if (ft_strncmp((const char *)chevrons, "<<", 3) == 0)
	{
		io->type = HEREDOC;
		io->io = clean_heredoc(io);
	}
	else if (ft_strncmp((const char *)chevrons, ">", 2) == 0)
	{
		io->type = OUTPUT_FILE;
		io->open_mode = O_WRONLY | O_CREAT | O_TRUNC;
	}
	else if (ft_strncmp((const char *)chevrons, ">>", 3) == 0)
	{
		io->type = OUTPUT_FILE;
		io->open_mode = O_WRONLY | O_CREAT | O_APPEND;
	}
	else
		io->type = -1;
}

void	*free_unsigned_ch_lst(t_data *data, t_io *io)
{
	t_io	*save;

	ft_error(errno, NULL, NULL, data);
	while (io != NULL)
	{
		save = io->next;
		ft_free((void **)&io);
		io = save;
	}
	return (NULL);
}

t_io	*mk_io(t_data *data, int command_block)
{
	char	*io;
	t_io	*start;
	t_io	*save;
	int		i;

	i = index_of_nth_block(data, command_block);
	start = NULL;
	while (data->lex_line[i] != NULL && is_pipe(data, i) == FALSE)
	{
		if (is_chevrons(data, i) == TRUE)
		{
			io = data->lex_line[i + 1];
			save = start;
			start = io_add_back(start, io, data);
			if (start == NULL)
				return (free_unsigned_ch_lst(data, save));
			fill_io_data(io_last(start), data->lex_line[i]);
			i++;
		}
		i++;
	}
	return (start);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:21:36 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/10 10:24:17 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	io_lexer(t_io *io, t_data *data)
{
	data->cur_cmd = NULL;
	io->exp_tab = (char *)ft_calloc(find_size(io->io, data) + 1,
			sizeof(char));
	if (io->exp_tab == NULL)
		return (ft_error(errno, NULL, NULL, data));
	if (io_env_var_exp(io, data) == FAIL)
		return (FAIL);
	if (io_line_cleaner(io->exp_io, data, io) == FAIL)
		return (FAIL);
	data->cur_cmd = io->io;
	return (SUCCES);
}

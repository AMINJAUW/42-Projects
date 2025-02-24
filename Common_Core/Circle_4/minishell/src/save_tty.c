/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_tty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:28:21 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/06 12:29:45 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_tty_fds(t_data *data)
{
	data->saved_tty_fds[0] = dup(STDIN_FILENO);
	if (data->saved_tty_fds[0] == -1)
		return (FAIL);
	data->saved_tty_fds[1] = dup(STDOUT_FILENO);
	if (data->saved_tty_fds[1] == -1)
	{
		close(data->saved_tty_fds[0]);
		return (FAIL);
	}
	return (SUCCES);
}

int	restore_tty(t_data *data)
{
	dup2(data->saved_tty_fds[0], STDIN_FILENO);
	dup2(data->saved_tty_fds[1], STDOUT_FILENO);
	return (SUCCES);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:24:30 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/02 14:31:46 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* If ptr is not NULL,frees it and assigns NULL as its value. */
void	ft_free(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
		return ;
	free(*ptr);
	*ptr = NULL;
}

void	close_fd_secure(int fd, t_data *data)
{
	if (fd != STDIN_FILENO && fd != data->saved_tty_fds[0]
		&& fd != STDOUT_FILENO && fd != data->saved_tty_fds[1])
		close (fd);
}

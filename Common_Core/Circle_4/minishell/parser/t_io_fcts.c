/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_io_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:09:25 by aminjauw          #+#    #+#             */
/*   Updated: 2023/09/18 17:08:23 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_io	*io_last(t_io *start)
{
	while (start->next != NULL)
	{
		start = start->next;
	}
	return (start);
}

void	io_free_all(t_io *start)
{
	t_io	*new_start;

	if (start == NULL)
		return ;
	new_start = start->next;
	ft_free((void **)&start->io);
	ft_free((void **)&start->exp_io);
	ft_free((void **)&start->exp_tab);
	ft_arclear(&start->split_exp_io);
	ft_free((void **)&start);
	while (new_start != NULL)
	{
		start = new_start;
		new_start = start->next;
		ft_free((void **)&start->io);
		ft_free((void **)&start->exp_io);
		ft_free((void **)&start->exp_tab);
		ft_arclear(&start->split_exp_io);
		ft_free((void **)&start);
	}
}

t_io	*io_add_back(t_io *start, char *io, t_data *data)
{
	t_io	*list;

	list = ft_calloc(1, sizeof(t_io));
	if (!list)
	{
		ft_error(errno, NULL, NULL, data);
		return (NULL);
	}
	list->io = io;
	list->heredoc_read_end = 0;
	list->exp_tab = NULL;
	list->next = NULL;
	if (start == NULL)
		start = list;
	else
		io_last(start)->next = list;
	return (start);
}

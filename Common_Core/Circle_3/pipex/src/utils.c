/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:21:28 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/30 11:26:02 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	close_mult(int n, ...)
{
	va_list	fd;
	int		i;

	i = 0;
	va_start(fd, n);
	while (i < n)
	{
		close(va_arg(fd, int));
		i++;
	}
	va_end(fd);
	return (0);
}

int	free_a(int number, ...)
{
	va_list	list;
	void	*addr;
	int		i;

	if (number > 0)
	{
		va_start(list, number);
		i = 0;
		while (i < number)
		{
			addr = va_arg(list, void *);
			if (addr != NULL)
				free(addr);
			else
				return (1);
			i++;
		}
		va_end(list);
	}
	return (0);
}

int	free_arr(int dim, void **arr)
{
	int	i;

	if (dim == 0)
		return (0);
	i = 0;
	while (arr[i] != NULL)
	{
		free_arr(dim - 1, (void **)arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

int	malloc_error(void *addr, int nbr, ...)
{
	va_list	to_free;
	int		i;

	if (addr != NULL)
		return (0);
	i = 0;
	va_start(to_free, nbr);
	while (i < nbr)
	{
		free_arr(va_arg(to_free, int), va_arg(to_free, void **));
		i++;
	}
	perror("Malloc error");
	return (1);
}

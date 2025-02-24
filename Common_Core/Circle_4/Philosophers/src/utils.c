/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:28:23 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/06 15:07:40 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free(void *addr)
{
	free(addr);
	return (0);
}

int	destroy_mutex(t_info *info, int tot)
{
	int	i;

	i = 0;
	while (i < tot)
	{
		pthread_mutex_destroy(&(info->forks[i]));
		i++;
	}
	return (0);
}

int	get_time(t_info *info)
{
	struct timeval	new;
	int				time;

	if (gettimeofday(&new, NULL))
		return (-1);
	time = (new.tv_sec * 1000) + (new.tv_usec / 1000);
	return (time - info->init_time);
}

int	your_turn(int a, int b, int var)
{
	b = min_to_zero(b);
	if (a < b)
		return (1);
	else
		return ((a - b) <= var);
}

int	div_1(int a, int b)
{
	int	i;

	i = a / b;
	if (a % b)
		return (i + 1);
	return (i);
}

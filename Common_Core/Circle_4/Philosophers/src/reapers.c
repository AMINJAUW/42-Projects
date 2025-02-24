/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reapers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 09:07:47 by aminjauw          #+#    #+#             */
/*   Updated: 2023/08/26 12:41:36 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	find_min_eat(t_info *info, int id)
{
	int	i;
	int	min;

	i = id * 5;
	min = INT_MAX;
	while (i < info->philo_nbr && i < (id * 5) + 5)
	{
		if (info->philo[i].lst_eat < min
			&& info->philo[i].eated != info->nb_to_eat)
			min = info->philo[i].lst_eat;
		i++;
	}
	return (min);
}

int	check_eat(t_reapers *reaper, int i, int enough)
{
	if (reaper->info->nb_to_eat != -1)
	{
		while (i < reaper->info->philo_nbr && i < (reaper->id * 5) + 5)
		{
			if (reaper->info->philo[i].eated == reaper->info->nb_to_eat)
				enough++;
			i++;
		}
	}
	return (enough);
}

int	min_to_zero(int i)
{
	if (i == INT_MIN)
		return (0);
	return (i);
}

void	real_reaper(t_reapers *reaper, int i)
{
	if (reaper->info->dead)
		return ;
	while (i < reaper->info->philo_nbr && i < (reaper->id * 5) + 5)
	{
		if (reaper->info->dead)
			return ;
		else if (get_time(reaper->info)
			- min_to_zero(reaper->info->philo[i].lst_eat)
			>= reaper->info->mt_die)
		{
			checking_eating(reaper->info);
			if (reaper->info->dead == FALSE)
				print(reaper->info, i + 1, "died", 1);
			reaper->info->dead = TRUE;
			break ;
		}
		i++;
	}
	return ;
}

void	*reaper(t_reapers *reaper)
{
	int	enough;
	int	i;

	while (!reaper->info->start)
		;
	while (!reaper->info->dead)
	{
		enough = 0;
		i = reaper->id * 5;
		reaper->min_eat = find_min_eat(reaper->info, reaper->id);
		enough = check_eat(reaper, i, enough);
		if ((enough == reaper->info->philo_nbr || enough == (reaper->id * 5)
				+ 5) && !reaper->info->dead)
		{
			reaper->eated = TRUE;
		}
		checking_eating(reaper->info);
		real_reaper(reaper, i);
	}
	return (0);
}

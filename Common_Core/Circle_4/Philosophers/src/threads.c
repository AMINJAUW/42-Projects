/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:54:28 by aminjauw          #+#    #+#             */
/*   Updated: 2025/02/24 20:24:30 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	uslp(int u_sec, t_info *info)
{
	int	init_time;

	init_time = get_time(info);
	while (get_time(info) < init_time + (u_sec) / 1000)
		usleep(1000);
	return (0);
}

int	mutex_unlock_two(pthread_mutex_t *one, pthread_mutex_t *two)
{
	pthread_mutex_unlock(one);
	pthread_mutex_unlock(two);
	return (0);
}

int	lock_unlock(t_philo *philo, int a, int b)
{
	pthread_mutex_lock(&(philo->info->forks[a]));
	print(philo->info, philo->id, "has taken a fork", 3);
	if (philo->info->dead || philo->info->philo_nbr == 1)
		return (1 + pthread_mutex_unlock(&(philo->info->forks[a])));
	pthread_mutex_lock(&(philo->info->forks[b]));
	print(philo->info, philo->id, "has taken a fork", 3);
	if (philo->info->dead)
		return (mutex_unlock_two(&(philo->info->forks[a]),
				&(philo->info->forks[b])));
	return (0);
}

int	tk_fork(t_philo *philo)
{
	int	ph_nbr;

	ph_nbr = philo->info->philo_nbr;
	while (!philo->info->dead && !your_turn(philo->lst_eat,
			philo->info->min_eated, 5))
		;
	if (philo->info->dead)
		return (0);
	if (philo->id % 2)
		return (lock_unlock(philo, philo->id % ph_nbr, philo->id - 1));
	else
		return (lock_unlock(philo, philo->id - 1, philo->id % ph_nbr));
}

void	*live(t_philo *ph)
{
	while (!ph->info->start)
		;
	while (!ph->info->dead)
	{
		if (ph->eated != ph->info->nb_to_eat)
		{
			if (tk_fork(ph) || !print(ph->info, ph->id, "is eating", 2))
				return (0);
			ph->lst_eat = get_time(ph->info);
			ph->eated++;
			if (ph->info->dead || uslp(ph->info->ut_eat, ph->info))
				return (0);
			if (mutex_unlock_two(&(ph->info->forks[ph->id - 1]),
					&(ph->info->forks[ph->id % ph->info->philo_nbr]))
				|| ph->eated == ph->info->nb_to_eat)
				return (0);
			print(ph->info, ph->id, "is sleeping", 0);
			if (ph->info->dead || uslp(ph->info->ut_sleep, ph->info))
				return (0);
			print(ph->info, ph->id, "is thinking", 0);
		}
		else
			return (0);
	}
	return (0);
}

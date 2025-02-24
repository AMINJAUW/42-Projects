/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:26:52 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/06 15:36:37 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mk_forks(t_info *info)
{
	int	i;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * (info->philo_nbr));
	if (!info->forks)
		return (0);
	while (i < info->philo_nbr)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL) != 0)
			return (destroy_mutex(info, i) + ft_free(info->forks));
		i++;
	}
	if (pthread_mutex_init(&info->mut_print, NULL))
		return (destroy_mutex(info, info->philo_nbr) + ft_free(info->forks));
	return (1);
}

int	init_philo(t_info *info)
{
	int	i;

	i = 0;
	info->philo = malloc(sizeof(t_philo) * info->philo_nbr);
	if (!info->philo)
		return (destroy_mutex(info, info->philo_nbr) + ft_free(info->forks));
	while (i < info->philo_nbr)
	{
		info->philo[i].id = i + 1;
		info->philo[i].lst_eat = INT_MIN;
		info->philo[i].eated = 0;
		info->philo[i].dead = FALSE;
		info->philo[i].info = info;
		if (pthread_create(&(info->philo[i].tread_id), NULL, (void *)live,
				(void *)&(info->philo[i])))
			return (destroy_mutex(info, info->philo_nbr)
				+ pthread_mutex_destroy(&(info->mut_print))
				+ ft_free(info->philo) + ft_free(info->forks));
		i++;
	}
	return (1);
}

int	init_reapers(t_info *info)
{
	int	i;

	i = 0;
	info->reapers = malloc(sizeof(t_reapers) * div_1(info->philo_nbr, 5));
	if (!info->reapers)
	{
		info->dead = TRUE;
		info->ut_eat = INT_MIN;
		return (0);
	}
	while (i < div_1(info->philo_nbr, 5))
	{
		info->reapers[i].id = i;
		info->reapers[i].info = info;
		if (pthread_create(&(info->reapers[i].tread_id), NULL, (void *)reaper,
				(void *)&(info->reapers[i])))
		{
			info->dead = TRUE;
			info->ut_eat = -i - 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_struct(t_info *info, int argc, char **argv)
{
	struct timeval	init;

	info->start = FALSE;
	info->philo_nbr = ft_atoi(argv[1], TRUE, -1);
	info->mt_die = ft_atoi(argv[2], TRUE, -1);
	info->ut_eat = ft_atoi(argv[3], TRUE, -1) * 1000;
	info->ut_sleep = ft_atoi(argv[4], TRUE, -1) * 1000;
	info->nb_to_eat = -1;
	if (argc == 6)
		info->nb_to_eat = ft_atoi(argv[5], TRUE, -1);
	if (info->philo_nbr < 1 || info->mt_die < 0 || info->ut_eat < 0
		|| info->ut_sleep < 0 || (argc == 6 && info->nb_to_eat < 0))
		return (1);
	info->dead = FALSE;
	if (!mk_forks(info))
		return (2);
	if (!init_philo(info))
		return (3);
	if (!init_reapers(info))
		return (4);
	gettimeofday(&init, NULL);
	info->init_time = init.tv_sec * 1000 + init.tv_usec / 1000;
	info->start = TRUE;
	return (0);
}

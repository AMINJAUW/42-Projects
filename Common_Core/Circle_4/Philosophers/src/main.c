/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:20:18 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/06 15:42:01 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print(t_info *info, int id, char *str, char color)
{
	int	i;

	if (info->dead)
		return (0);
	pthread_mutex_lock(&(info->mut_print));
	i = printf("%5i : \x1b[3%im%02i %s\x1b[0m\n", get_time(info), color, id,
			str);
	pthread_mutex_unlock(&(info->mut_print));
	return (i);
}

void	ending_process(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	if (info->ut_eat != INT_MIN)
	{
		j = div_1(info->philo_nbr, 5) * (info->ut_eat > -1) + -(info->ut_eat
				+ 1) * (info->ut_eat < 0);
		while (i < j)
			pthread_join(info->reapers[i++].tread_id, NULL);
		i = 0;
	}
	if (info->ut_eat != INT_MIN)
		free(info->reapers);
	while (i < info->philo_nbr)
	{
		pthread_join(info->philo[i].tread_id, NULL);
		i++;
	}
	destroy_mutex(info, info->philo_nbr);
	pthread_mutex_destroy(&(info->mut_print));
	free(info->forks);
	free(info->philo);
	free(info);
}

void	checking_eating(t_info *info)
{
	int	i;
	int	tot_eated;
	int	nb_reapers;
	int	min;

	nb_reapers = div_1(info->philo_nbr, 5);
	i = 0;
	tot_eated = 0;
	min = INT_MAX;
	while (i < nb_reapers)
	{
		if (info->reapers[i].eated)
			tot_eated++;
		if (info->reapers[i].min_eat < min)
			min = info->reapers[i].min_eat;
		i++;
	}
	info->min_eated = min;
	if (tot_eated == nb_reapers)
	{
		info->dead = TRUE;
	}
}

int	main(int argc, char **argv)
{
	t_info	*info;
	int		i;

	if (argc != 5 && argc != 6)
		return (1 + printf("Wrong number of args\n"));
	info = malloc(sizeof(t_info));
	if (!info)
		return (printf("Malloc allocation error\n"));
	i = init_struct(info, argc, argv);
	if (i && ((i == 1 && printf("Pease put valid arguments\n")) || (i == 2
				&& printf("Mutex_Error maybe just try again\n")) || (i == 3
				&& printf("pthread_error maybe just try again\n")))
		&& !ft_free(info))
		return (i);
	while (!info->dead)
		checking_eating(info);
	ending_process(info);
	return (0);
}

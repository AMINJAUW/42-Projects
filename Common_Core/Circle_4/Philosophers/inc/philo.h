/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:20:53 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/06 15:07:14 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

struct	s_info;

typedef struct s_reapers
{
	int				id;
	int				eated;
	int				min_eat;
	pthread_t		tread_id;
	struct s_info	*info;
}					t_reapers;

typedef struct s_philo
{
	int				id;
	int				lst_eat;
	int				eated;
	int				dead;
	pthread_t		tread_id;
	struct s_info	*info;
}					t_philo;

typedef struct s_info
{
	int				start;
	int				philo_nbr;
	int				mt_die;
	int				ut_eat;
	int				ut_sleep;
	int				min_eated;
	int				nb_to_eat;
	int				dead;
	int				init_time;
	t_philo			*philo;
	t_reapers		*reapers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mut_print;
}					t_info;

/*----------Prototypes-----------*/
int					ft_atoi(const char *str, int only_num, int error);
void				*live(t_philo *philo);
int					init_struct(t_info *info, int argc, char **argv);
int					get_time(t_info *info);
int					destroy_mutex(t_info *info, int tot);
int					ft_free(void *addr);
int					print(t_info *info, int id, char *str, char color);
int					your_turn(int a, int b, int var);
int					div_1(int a, int b);
void				*reaper(t_reapers *reaper);
int					uslp(int u_sec, t_info *info);
void				checking_eating(t_info *info);
int					min_to_zero(int i);

#endif
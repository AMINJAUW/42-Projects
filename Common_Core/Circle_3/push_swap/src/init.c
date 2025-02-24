/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:05:17 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/09 10:15:12 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	init_max_min(t_arr *tabs)
{
	ft_find_max(tabs, A);
	ft_find_max(tabs, B);
	ft_find_min(tabs, A);
	ft_find_min(tabs, B);
	return (1);
}

int	ft_only_zero(char *str)
{
	while (*str)
	{
		if (*str != '0')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int	ft_init_struct(int argc, char **argv, t_arr *tabs)
{
	int	i;
	int	temp;

	tabs->a = ft_calloc(argc, sizeof(int));
	if (!tabs->a)
		return (0);
	tabs->b = ft_calloc(argc, sizeof(int));
	if (!tabs->b)
		return (0);
	tabs->len_b = 0;
	tabs->len_a = argc - 1;
	i = 0;
	while (++i < argc)
	{
		temp = ft_atoi((const char *)argv[i]);
		if (temp == 0 && !ft_only_zero(argv[i]))
			return (0);
		tabs->a[i - 1] = temp;
	}
	return (init_max_min(tabs));
}

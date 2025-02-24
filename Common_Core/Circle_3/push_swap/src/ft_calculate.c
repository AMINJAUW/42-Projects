/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:54:29 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/03 18:19:13 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_is_sorted(int *tab, int len, int increase)
{
	int	i;
	int	temp;

	i = 0;
	temp = INT_MIN * (!!increase) + INT_MAX * (!increase);
	while (i < len)
	{
		if (((tab[i] < temp) && increase) || ((tab[i] > temp) && !increase))
			return (FALSE);
		temp = tab[i];
		i++;
	}
	return (TRUE);
}

int	ft_rot_sort(t_arr *tabs, int a, int increasing)
{
	int	i;

	if (increasing)
		i = ft_find_min(tabs, a);
	else
		i = ft_find_max(tabs, a);
	if ((a && i < tabs->len_a - i) || (!a && i < tabs->len_b - i))
	{
		while (i > 0)
		{
			ft_r(tabs, a);
			i--;
		}
	}
	else
	{
		while (i < tabs->len_a)
		{
			ft_rrab(tabs, a);
			i++;
		}
	}
	return (1);
}

int	ft_calculate(t_arr *tabs)
{
	if (ft_is_sorted(tabs->a, tabs->len_a, TRUE))
		return (1);
	else if (tabs->len_a < 6)
	{
		ft_sort_small(tabs, tabs->len_a);
		return (ft_rot_sort(tabs, A, TRUE));
	}
	if (!ft_sort_big(tabs))
		return (0);
	return (ft_rot_sort(tabs, A, TRUE));
}

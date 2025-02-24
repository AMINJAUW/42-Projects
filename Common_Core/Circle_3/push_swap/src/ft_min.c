/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:15:42 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/03 11:55:43 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_new_min(t_arr *tabs, int a, int min)
{
	if (a)
	{
		tabs->min_a = min;
		return (0);
	}
	tabs->min_b = min;
	return (0);
}

int	ft_find_min(t_arr *tabs, int a)
{
	int	i;
	int	j;
	int	min;
	int	*tab;
	int	len;

	min = INT_MAX;
	i = 0;
	tab = tabs->a;
	len = tabs->len_a;
	if (!a)
	{
		tab = tabs->b;
		len = tabs->len_b;
	}
	while (i < len)
	{
		if (tab[i] <= min)
		{
			j = i;
			min = tab[i] + ft_new_min(tabs, a, tab[i]);
		}
		i++;
	}
	return ((len != 0) * j + ft_new_min(tabs, a, min));
}

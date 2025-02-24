/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:10:07 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/04 16:16:26 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_new_max(t_arr *tabs, int a, int max)
{
	if (a)
	{
		tabs->max_a = max;
		return (0);
	}
	tabs->max_b = max;
	return (0);
}

int	ft_find_max(t_arr *tabs, int a)
{
	int	i;
	int	j;
	int	max;
	int	*tab;
	int	len;

	max = INT_MIN;
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
		if (tab[i] >= max)
		{
			j = i;
			max = tab[i] + ft_new_max(tabs, a, tab[i]);
		}
		i++;
	}
	return ((len != 0) * j + ft_new_max(tabs, a, max));
}

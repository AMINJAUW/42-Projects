/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_small.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:24:21 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/09 09:38:10 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_len3(t_arr *tabs)
{
	int	i_max;
	int	i_min;

	if (ft_is_sorted(tabs->a, tabs->len_a, TRUE))
		return ;
	i_max = ft_find_max(tabs, A);
	i_min = ft_find_min(tabs, A);
	if (i_max == 0)
	{
		if (i_min == 1)
			ft_r(tabs, A);
		else
			ft_s(tabs, A);
	}
	else if (i_max != 0 && i_min == 1)
		ft_s(tabs, A);
	else if (i_max != 0 && i_min != 0)
		ft_rrab(tabs, A);
	else
		ft_s(tabs, A);
	return (ft_len3(tabs));
}

void	ft_sort_small(t_arr *tabs, int nb)
{
	int	i;

	i = 0;
	if (nb == 2)
		return (ft_r(tabs, A));
	if (nb == 3)
		return (ft_len3(tabs));
	while (nb - i > 3)
	{
		ft_p(tabs, B);
		i++;
	}
	ft_sort_small(tabs, tabs->len_a);
	while (i > 0)
	{
		ft_arange_one_more(tabs, A);
		i--;
	}
}

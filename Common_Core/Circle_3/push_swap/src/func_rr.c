/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_rr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:20:05 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/03 11:10:05 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_rra_temp(t_arr *tabs, int both_in_one)
{
	int	temp;
	int	i;

	i = tabs->len_a - 1;
	if (tabs->len_a)
	{
			temp = tabs->a[i];
		while (i >= 1)
		{
			tabs->a[i] = tabs->a[i - 1];
			i--;
		}
		tabs->a[0] = temp;
	}
	if (!both_in_one)
		ft_printf("rra\n");
}

static void	ft_rrb_temp(t_arr *tabs, int both_in_one)
{
	int	temp;
	int	i;

	i = tabs->len_b - 1;
	if (tabs->len_b)
	{
			temp = tabs->b[i];
		while (i >= 1)
		{
			tabs->b[i] = tabs->b[i - 1];
			i--;
		}
		tabs->b[0] = temp;
	}
	if (!both_in_one)
		ft_printf("rrb\n");
}

void	ft_rrab(t_arr *tabs, int a)
{
	if (a)
		return (ft_rra_temp(tabs, 0));
	return (ft_rrb_temp(tabs, 0));
}

void	ft_rrr(t_arr *tabs)
{
	ft_rra_temp(tabs, 1);
	ft_rrb_temp(tabs, 1);
	ft_printf("rrr\n");
}

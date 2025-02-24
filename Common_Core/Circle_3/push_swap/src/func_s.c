/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:21:56 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/03 11:11:37 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_sa_temp(t_arr *tabs, int both_in_one)
{
	int	temp;

	if (tabs->len_a > 1)
	{
		temp = tabs->a[0];
		tabs->a[0] = tabs->a[1];
		tabs->a[1] = temp;
	}
	if (!both_in_one)
		ft_printf("sa\n");
}

static void	ft_sb_temp(t_arr *tabs, int both_in_one)
{
	int	temp;

	if (tabs->len_b > 1)
	{
		temp = tabs->b[0];
		tabs->b[0] = tabs->b[1];
		tabs->b[1] = temp;
	}
	if (!both_in_one)
		ft_printf("sb\n");
}

void	ft_s(t_arr *tabs, int a)
{
	if (a)
		return (ft_sa_temp(tabs, 0));
	return (ft_sb_temp(tabs, 0));
}

void	ft_ss(t_arr *tabs)
{
	ft_sa_temp(tabs, 1);
	ft_sb_temp(tabs, 1);
	ft_printf("ss\n");
}

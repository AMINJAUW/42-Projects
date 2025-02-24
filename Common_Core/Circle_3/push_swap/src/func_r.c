/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:03:11 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/03 11:07:34 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_ra_temp(t_arr *tabs, int both_in_one)
{
	int	temp;
	int	i;

	i = 0;
	if (tabs->len_a)
	{		
		temp = tabs->a[i];
		while (i <= tabs->len_a - 2)
		{
			tabs->a[i] = tabs->a[i + 1];
			i++;
		}
		tabs->a[tabs->len_a - 1] = temp;
	}
	if (!both_in_one)
		ft_printf("ra\n");
}

static void	ft_rb_temp(t_arr *tabs, int both_in_one)
{
	int	temp;
	int	i;

	i = 0;
	if (tabs->len_b)
	{	
		temp = tabs->b[i];
		while (i <= tabs->len_b - 2)
		{
			tabs->b[i] = tabs->b[i + 1];
			i++;
		}
		tabs->b[tabs->len_b - 1] = temp;
	}
	if (!both_in_one)
		ft_printf("rb\n");
}

void	ft_r(t_arr *tabs, int a)
{
	if (a)
		return (ft_ra_temp(tabs, 0));
	return (ft_rb_temp(tabs, 0));
}

void	ft_rr(t_arr *tabs)
{
	ft_ra_temp(tabs, 1);
	ft_rb_temp(tabs, 1);
	ft_printf("rr\n");
}

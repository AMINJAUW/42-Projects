/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:30:33 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/04 16:18:05 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_move_index_to_front(t_arr *tabs, int a)
{
	int	i;

	i = 0;
	if (a)
	{
		while (i < tabs->len_a)
		{
			tabs->a[i] = tabs->a[i + 1];
			i++;
		}
		tabs->len_a--;
	}
	else
	{
		while (i < tabs->len_b)
		{
			tabs->b[i] = tabs->b[i + 1];
			i++;
		}
		tabs->len_b--;
	}
}

static void	ft_move_index_to_back(t_arr *tabs, int a)
{
	int	i;

	if (a)
	{
		i = tabs->len_a;
		while (i >= 1)
		{
			tabs->a[i] = tabs->a[i - 1];
			i--;
		}
		tabs->len_a++;
	}
	else
	{
		i = tabs->len_b;
		while (i >= 1)
		{
			tabs->b[i] = tabs->b[i - 1];
			i--;
		}
		tabs->len_b++;
	}
}

static void	ft_pa(t_arr *tabs)
{
	if (tabs->len_b)
	{
		ft_move_index_to_back(tabs, A);
		tabs->a[0] = tabs->b[0];
		if (tabs->a[0] > tabs->max_a)
			ft_new_max(tabs, A, tabs->a[0]);
		else if (tabs->a[0] < tabs->min_a)
			ft_new_min(tabs, A, tabs->a[0]);
		ft_move_index_to_front(tabs, B);
		ft_find_max(tabs, B);
		ft_find_min(tabs, B);
	}
	ft_printf("pa\n");
}

static void	ft_pb(t_arr *tabs)
{
	if (tabs->len_a)
	{
		ft_move_index_to_back(tabs, B);
		tabs->b[0] = tabs->a[0];
		if (tabs->b[0] > tabs->max_b)
			ft_new_max(tabs, B, tabs->b[0]);
		else if (tabs->b[0] < tabs->min_b)
			ft_new_min(tabs, B, tabs->b[0]);
		ft_move_index_to_front(tabs, A);
		ft_find_max(tabs, A);
		ft_find_min(tabs, A);
	}
	ft_printf("pb\n");
}

void	ft_p(t_arr *tabs, int a)
{
	if (a)
		return (ft_pa(tabs));
	return (ft_pb(tabs));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:35:52 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/04 16:11:18 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_abs(int i)
{
	if (i < 0)
		return (-1 * i);
	return (i);
}

int	ft_sign(int i)
{
	if (i < 0)
		return (-1);
	return (1);
}

void	ft_fill_tab(t_arr *tabs, int **pos_moves)
{
	int	i;
	int	len;

	i = 0;
	len = tabs->len_b;
	while (i < len)
	{
		pos_moves[0][i] = ft_should_be(tabs, tabs->b[i], A);
		if (i < len - i)
			pos_moves[1][i] = i;
		else
			pos_moves[1][i] = i - len;
		if (pos_moves[0][i] < tabs->len_a - pos_moves[0][i])
			pos_moves[2][i] = pos_moves[0][i];
		else
			pos_moves[2][i] = pos_moves[0][i] - tabs->len_a;
		i++;
	}
}

static int	ft_update_best(t_arr *tabs, int **pos_moves)
{
	int	best[2];
	int	i;
	int	sum;

	i = -1;
	best[1] = INT_MAX;
	while (++i < tabs->len_b)
	{
		if (!ft_same_sign(pos_moves[1][i], pos_moves[2][i]))
			sum = ft_abs(pos_moves[1][i]) + ft_abs(pos_moves[2][i]);
		else
			sum = ft_abs(pos_moves[1][i])
				* (ft_abs(pos_moves[1][i]) >= ft_abs(pos_moves[2][i]))
				+ ft_abs(pos_moves[2][i])
				* (ft_abs(pos_moves[2][i]) > ft_abs(pos_moves[1][i]));
		if (sum < best[1] && (i < 6 || tabs->len_b - i < 4))
		{
			best[1] = sum;
			best[0] = i;
		}
	}
	return (best[0]);
}

void	ft_put_best_on_top(t_arr *tabs, int **pos_moves)
{
	int	both;
	int	best;

	best = ft_update_best(tabs, pos_moves);
	while (pos_moves[1][best] != 0)
	{
		both = (pos_moves[2][best] != 0
				&& ft_same_sign(pos_moves[1][best], pos_moves[2][best]));
		if (pos_moves[1][best] > 0)
		{
			if ((1 + pos_moves[2][best]--) && both)
				ft_rr(tabs);
			else
				ft_r(tabs, B);
		}
		else
		{
			if ((1 - pos_moves[2][best]++) && both)
				ft_rrr(tabs);
			else
				ft_rrab(tabs, B);
		}
		pos_moves[1][best] += -1 * ft_sign(pos_moves[1][best]);
	}
}

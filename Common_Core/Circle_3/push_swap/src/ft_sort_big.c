/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_big.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:43:11 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/04 16:20:13 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_first_in_perc(t_arr *tabs, int a, float perc)
{
	int	i;
	int	counter;
	int	*arr;
	int	len;

	arr = tabs->a;
	len = tabs->len_a;
	if (!a)
	{
		arr = tabs->b;
		len = tabs->len_b;
	}
	i = 0;
	counter = 0;
	while (++i < len)
		counter += arr[i] < arr[0];
	return (counter <= len * perc);
}

/* matrix of arrays with the first array related to 
	the first element of b
	example ; pos_moves[n] = (x, -y, -z)
	so for the nth number of 'b' its position in 'a' should be x
	and to have nth number in front of 'b' you should rotate be (-y) times
	and to have the good position you should rotate 'a' (-z) times.
	
	if de sence of rotation matches for a and b to rr instead;
*/

int	where_next_b_should_be(t_arr *tabs)
{
	int	*pos_moves[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		pos_moves[i] = ft_calloc(tabs->len_b + 1, sizeof(int));
		if (!pos_moves[i])
		{
			while (i > 0)
				free(pos_moves[--i]);
			return (0);
		}
		i++;
	}
	ft_fill_tab(tabs, pos_moves);
	ft_put_best_on_top(tabs, pos_moves);
	ft_free_a(3, pos_moves[0], pos_moves[1], pos_moves[2]);
	return (1);
}

int	ft_sort_big(t_arr *tabs)
{
	while (tabs->len_a > 5)
	{
		if (is_first_in_perc(tabs, A, 0.3))
			ft_p(tabs, B);
		else
			ft_r(tabs, A);
	}
	ft_sort_small(tabs, 5);
	while (tabs->len_b != 0)
	{
		if (!where_next_b_should_be(tabs))
			return (0);
		ft_arange_one_more(tabs, A);
	}
	ft_rot_sort(tabs, A, TRUE);
	return (1);
}

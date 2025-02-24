/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:43:22 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/03 18:49:44 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_same_sign(int a, int b)
{
	if (a * b >= 0)
		return (TRUE);
	return (FALSE);
}

static int	ft_is_between(t_arr *tabs, int i, int a, int number)
{
	if (i == 0)
	{
		if (a && (number < tabs->a[0]
				&& number > tabs->a[tabs->len_a - 1]))
			return (TRUE);
		else if (!a && (number < tabs->b[0]
				&& number > tabs->b[tabs->len_b - 1]))
			return (TRUE);
		else
			return (FALSE);
	}
	else
	{
		if (a && (number < tabs->a[i] && number > tabs->a[i - 1]))
			return (TRUE);
		else if (!a && (number < tabs->b[i] && number > tabs->b[i - 1]))
			return (TRUE);
		else
			return (FALSE);
	}
}

int	ft_should_be(t_arr *tabs, int number, int a)
{
	int	i;
	int	min_pos;
	int	max_pos;

	i = 0;
	if ((a && tabs->len_a == 0) || (!a && tabs->len_b == 0))
		return (0);
	max_pos = ft_find_max(tabs, a);
	if ((a && number > tabs->max_a) || (!a && number > tabs->max_b))
		return ((max_pos + 1) * (max_pos + 1 != tabs->len_a));
	min_pos = ft_find_min(tabs, a);
	if ((a && number < tabs->min_a) || (!a && number < tabs->min_b))
		return (min_pos);
	while (i < tabs->len_a && !ft_is_between(tabs, i, a, number))
		i++;
	return (i);
}

void	ft_arange_one_more(t_arr *tabs, int a)
{
	int	i;
	int	j;
	int	num;

	num = tabs->a[0] * !a + tabs->b[0] * a;
	i = ft_should_be(tabs, num, a);
	j = 0;
	if ((a && i < tabs->len_a - i) || (!a && i < tabs->len_b - i))
	{
		while (j < i)
		{
			ft_r(tabs, a);
			j++;
		}
	}
	else
	{
		while (j < tabs->len_a - i)
		{
			ft_rrab(tabs, a);
			j++;
		}
	}
	ft_p(tabs, a);
}

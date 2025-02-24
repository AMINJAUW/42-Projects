/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:52:11 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/15 10:33:17 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_free_split(char **words, int i)
{
	int	j;

	j = 0;
	while (j < i || words[j] != 0)
	{
		free(words[j]);
		j++;
	}
	free(words);
	return (0);
}

int	ft_init_struct_str(int argc, char **argv, t_arr *tabs)
{
	char	**numbers;
	int		i;
	int		temp;

	numbers = ft_split((const char *)argv[1], ' ');
	argc = 0;
	while (numbers[argc] != 0)
		argc++;
	tabs->a = ft_calloc(argc + 1, sizeof(int));
	if (!tabs->a)
		return (0);
	tabs->b = ft_calloc(argc + 1, sizeof(int));
	if (!tabs->b)
		return (0);
	tabs->len_b = 0;
	tabs->len_a = argc;
	i = -1;
	while (++i < argc)
	{
		temp = ft_atoi((const char *)numbers[i]);
		if (temp == 0 && !ft_only_zero(numbers[i]))
			return (ft_free_split(numbers, i));
		tabs->a[i] = temp;
	}
	return (init_max_min(tabs) + ft_free_split(numbers, argc));
}

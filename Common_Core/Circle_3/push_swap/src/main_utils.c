/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:39:11 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/15 10:36:16 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_free_a(int number, ...)
{
	va_list	list;
	void	*addr;
	int		i;

	if (number > 0)
	{
		va_start(list, number);
		i = 0;
		while (i < number)
		{
			addr = va_arg(list, void *);
			if (addr != NULL)
				free(addr);
			else
				return (0);
			i++;
		}
		va_end(list);
	}
	return (0);
}

static int	ft_check_duplicate(t_arr *tabs)
{
	int	i;
	int	j;

	i = 0;
	while (i < tabs->len_a)
	{
		j = 0;
		while (j < tabs->len_a)
		{
			if (i != j && tabs->a[i] == tabs->a[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	process(int argc, char **argv, int bonus)
{
	t_arr	*tabs;

	if (argc == 1)
		exit(1);
	tabs = malloc(sizeof(t_arr));
	if (!tabs)
		return (0);
	if (argc == 2 && (!ft_init_struct_str(argc, argv, tabs)
			|| ft_check_duplicate(tabs)) && ft_printf("Error\n"))
		return (ft_free_a(2, tabs->a, tabs->b) + ft_free_a(1, tabs));
	else if (argc != 2 && (!ft_init_struct(argc, argv, tabs)
			|| ft_check_duplicate(tabs)) && ft_printf("Error\n"))
		return (ft_free_a(2, tabs->a, tabs->b) + ft_free_a(1, tabs));
	if (!ft_calculate(tabs))
		return (ft_printf("Error\n"));
	if (bonus && ft_is_sorted(tabs->a, tabs->len_a, TRUE))
		ft_printf("OK\n");
	if (!bonus && !ft_is_sorted(tabs->a, tabs->len_a, TRUE))
		ft_printf("KO\n");
	return (ft_free_a(3, tabs->a, tabs->b, tabs));
}

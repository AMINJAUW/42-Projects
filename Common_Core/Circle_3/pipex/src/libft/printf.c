/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:01:08 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/21 11:04:50 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print	*init_info(t_print *tab, int *nb_print, int first)
{
	if (!first)
		*nb_print += tab->printed;
	tab->width = 0;
	tab->precision = 0;
	tab->zero = 0;
	tab->point = 0;
	tab->dash = 0;
	tab->printed = 0;
	tab->plus = 0;
	tab->hash = 0;
	tab->space = 0;
	tab->neg = 0;
	tab->wrong = 0;
	return (tab);
}

int	free_all(t_print *tab, int string, ...)
{
	va_list	strings;
	char	*freed;

	if (!string)
	{
		va_end(tab->args);
		free(tab);
		return (-1);
	}
	va_start(strings, string);
	while (string > 0)
	{
		freed = va_arg(strings, void *);
		if (freed[0] != 0)
			free(freed);
		string--;
	}
	va_end(strings);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	t_print	*print_info;
	int		i;
	int		nb_print;

	print_info = malloc(sizeof(t_print));
	if (!print_info)
		return (-1);
	va_start(print_info->args, format);
	i = 0;
	nb_print = 0;
	init_info(print_info, &nb_print, 1);
	while (format[i])
	{
		while (format[i] && format[i] != '%')
			nb_print += write(1, &(format[i++]), 1);
		if (format[i] == '%')
		{
			i = print_format(print_info, (char *)format, i);
			if (i < 0)
				return (free_all(print_info, 0));
			init_info(print_info, &nb_print, 0);
		}
	}
	free_all(print_info, 0);
	return (nb_print);
}

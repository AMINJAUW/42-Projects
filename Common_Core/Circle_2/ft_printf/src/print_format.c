/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:44:23 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/21 11:01:38 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (charset[i]);
		i++;
	}
	return (0);
}

int	add_info(t_print *tab, char c)
{
	if (c == '0')
		tab->zero = 1;
	else if (c == '.')
		tab->point = 1;
	else if (c == '-')
		tab->dash = 1;
	else if (c == ' ')
		tab->space = 1;
	else if (c == '#')
		tab->hash = 1;
	else if (c == '+')
		tab->plus = 1;
	else if (!is_in_charset(c, "0.- #+"))
		tab->wrong = 1;
	return (1);
}

int	write_format(t_print *tab, char c)
{
	int	i;

	if (tab->wrong || c == 0)
		return (0);
	if (c == 'c')
		i = ft_print_char(tab);
	if (c == 's')
	{
		i = ft_print_string(tab);
		if (i == 2)
			tab->printed += write(1, "(null)", 6);
	}
	if (c == 'p')
		i = ft_print_address(tab);
	if (c == 'd' || c == 'i')
		i = ft_print_int(tab);
	if (c == 'u')
		i = ft_print_uint(tab);
	if (c == 'x')
		i = ft_print_lowhex(tab);
	if (c == 'X')
		i = ft_print_highhex(tab);
	if (c == '%')
		i = ft_print_percent(tab);
	return (i == 1);
}

int	print_format(t_print *tab, char *format, int i)
{
	i ++;
	while (!is_in_charset(format[i], "cspdiuxX%") && format[i])
	{
		if (ft_isdigit(format[i]))
		{
			if (tab->point)
			{
				tab->precision = ft_atoi(&(format[i]));
				while (ft_isdigit(format[i]) && (format[i]))
					i++;
			}
			else if (format[i] != '0' )
			{
				tab->width = ft_atoi(&(format[i]));
				while (ft_isdigit(format[i]) && (format[i]))
					i++;
			}
			else if (!tab->point && format[i] == '0')
				add_info(tab, format[i++]);
		}
		else
			add_info(tab, format[i++]);
	}
	i += -2147483648 * !write_format(tab, format[i]);
	return (i + 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_csp%.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:36:51 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/19 11:37:31 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(t_print *tab)
{
	char	c;

	c = (char)va_arg(tab->args, int);
	if (tab->width)
	{
		if (tab->dash)
			tab->printed += write(1, &c, 1);
		while (tab->printed < tab->width - !tab->dash)
			tab->printed += write(1, " ", 1);
		if (!tab->dash)
			tab->printed += write(1, &c, 1);
	}
	else
		tab->printed += write(1, &c, 1);
	return (1);
}

int	ft_print_string(t_print *tab)
{
	char	*str;
	int		len;

	str = va_arg(tab->args, char *);
	if (!str)
		str = NULLP;
	if (*str == 0 && !tab->width)
		return (1);
	len = (int)ft_strlen(str)
		* (tab->precision > (int)ft_strlen(str) || !tab->point)
		+ tab->precision * (tab->precision <= (int)ft_strlen(str));
	if (tab->width)
	{
		if (tab->dash)
			tab->printed += write(1, str, len);
		while (tab->printed < tab->width - (!tab->dash * len))
			tab->printed += write(1, " ", 1);
		if (!tab->dash)
			tab->printed += write(1, str, len);
	}
	else
		tab->printed += write(1, str, len);
	return (1);
}

int	ft_print_address(t_print *tab)
{
	unsigned long long	num;
	char				*s_num;
	char				c;
	int					len;

	tab->hash = 1;
	num = va_arg(tab->args, unsigned long long);
	s_num = base_change(num, LOWHEX);
	if (!s_num)
		return (0);
	s_num = make_patted_num(tab, s_num, (long long)num);
	if (!s_num)
		return (0 + free_all(tab, 1, s_num));
	if (tab->hash)
		return (print_hash(tab, s_num, 'x'));
	len = (int)ft_strlen(s_num);
	if (tab->dash)
		tab->printed += write(1, s_num, len);
	c = '0' * tab->zero * !tab->dash + ' ' * (tab->dash || !tab->zero);
	while (tab->printed < tab->width - !tab->dash * len)
		tab->printed += write(1, &c, 1);
	if (!tab->dash)
		tab->printed += write(1, s_num, len);
	return (1 + free_all(tab, 1, s_num));
}

int	ft_print_percent(t_print *tab)
{
	char	c;

	c = '0' * tab->zero * !tab->dash + ' ' * (!tab->zero || tab->dash);
	if (tab->dash)
		tab->printed += write(1, "%", 1);
	while (tab->printed < tab->width - !tab->dash)
		tab->printed += write(1, &c, 1);
	if (!tab->dash)
		tab->printed += write(1, "%", 1);
	return (1);
}

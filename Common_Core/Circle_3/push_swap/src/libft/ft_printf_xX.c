/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xX.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:56:38 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/20 16:11:10 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	base_number_size(unsigned long long num, int base_len)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= base_len;
		i++;
	}
	return (i);
}

char	*base_change(unsigned long long num, char *base)
{
	int		base_len;
	char	*s_num;
	int		s_num_len;
	int		i;

	base_len = ft_strlen(base);
	s_num_len = base_number_size(num, base_len);
	s_num = malloc(sizeof(char) * (1 + s_num_len));
	if (!s_num)
		return (0);
	i = 0;
	if (num == 0)
		s_num[0] = '0';
	while (i < s_num_len && num != 0)
	{
		s_num[s_num_len - 1 - i] = base[num % base_len];
		num /= base_len;
		i ++;
	}
	s_num[s_num_len] = 0;
	return (s_num);
}

int	print_hash(t_print *tab, char *s_num, char x)
{
	int	c;

	c = '0' * tab->zero * !tab->dash * (!tab->point || (tab->precision < 0))
		+ ' ' * (tab->dash || !tab->zero || tab->point);
	if (tab->dash || (tab->zero && (!tab->point || (tab->precision < 0))))
	{
		tab->printed += write(1, "0", 1);
		tab->printed += write(1, &x, 1);
		if (tab->dash)
			tab->printed += write(1, s_num, (int)ft_strlen(s_num));
		while (tab->printed < tab->width - !tab->dash * (int)ft_strlen(s_num))
			tab->printed += write(1, &c, 1);
		if (!tab->dash)
			tab->printed += write(1, s_num, (int)ft_strlen(s_num));
	}
	else
	{
		while (tab->printed < tab->width - (int)ft_strlen(s_num) - 2)
			tab->printed += write(1, &c, 1);
		tab->printed += write(1, "0", 1);
		tab->printed += write(1, &x, 1);
		tab->printed += write(1, s_num, (int)ft_strlen(s_num));
	}
	return (1 + free_all(tab, 1, s_num));
}

int	ft_print_lowhex(t_print *tab)
{
	unsigned int	num;
	char			*s_num;
	int				len;
	char			c;

	num = va_arg(tab->args, unsigned int);
	s_num = base_change(num, LOWHEX);
	if (!s_num)
		return (0);
	s_num = make_patted_num(tab, s_num, (long long)num);
	if (!s_num)
		return (0);
	if (num != 0 && tab->hash)
		return (print_hash(tab, s_num, 'x'));
	len = ft_strlen(s_num);
	tab->printed += print_front_sign(tab, 0, s_num, 0);
	if (tab->dash)
		tab->printed += write(1, s_num, len);
	c = '0' * tab->zero * !tab->dash + ' ' * (tab->dash || !tab->zero);
	while (tab->printed < tab->width - !tab->dash * len)
		tab->printed += write(1, &c, 1);
	if (!tab->dash)
		tab->printed += write(1, s_num, len);
	return (1 + free_all(tab, 1, s_num));
}

int	ft_print_highhex(t_print *tab)
{
	unsigned int	num;
	char			*s_num;
	int				len;
	char			c;

	num = va_arg(tab->args, unsigned int);
	s_num = base_change(num, HIGHHEX);
	if (!s_num)
		return (0);
	s_num = make_patted_num(tab, s_num, (long long)num);
	if (!s_num)
		return (0);
	if (num != 0 && tab->hash)
		return (print_hash(tab, s_num, 'X'));
	len = ft_strlen(s_num);
	tab->printed += print_front_sign(tab, 0, s_num, 0);
	if (tab->dash)
		tab->printed += write(1, s_num, len);
	c = '0' * tab->zero * !tab->dash + ' ' * (tab->dash || !tab->zero);
	while (tab->printed < tab->width - !tab->dash * len)
		tab->printed += write(1, &c, 1);
	if (!tab->dash)
		tab->printed += write(1, s_num, len);
	return (1 + free_all(tab, 1, s_num));
}

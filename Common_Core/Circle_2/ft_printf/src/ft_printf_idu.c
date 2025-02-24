/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_idu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:48:37 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/19 10:28:29 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*zero_case(t_print *tab, long long num, char *s_num)
{
	static char	*new = "";

	if (num == 0 && tab->point && !tab->precision)
	{
		free(s_num);
		tab->zero = 0;
		return (new);
	}
	return (s_num);
}

char	*make_patted_num(t_print *tab, char *s_num, long long num)
{
	int		len;
	char	*front;
	int		prec;
	char	*out;

	len = ft_strlen(s_num);
	prec = tab->precision - len;
	out = zero_case(tab, num, s_num);
	if (len < tab->precision)
	{
		front = malloc(sizeof(char) * (1 + (prec > 0) * prec));
		if (!front)
			return (0);
		len = 0;
		while (len < (prec > 0) * prec)
			front[len++] = '0';
		front[len] = 0;
		out = ft_strjoin((const char *)front, (const char *)s_num);
		return (out + free_all(tab, 2, s_num, front));
	}
	return (out);
}

int	print_front_sign(t_print *tab, int after, char *s_num, int is_int)
{
	int		i;
	char	c;
	int		len;

	i = 0;
	if ((tab->point && tab->precision >= 0))
		tab->zero = 0;
	c = !tab->neg *('+' * tab->plus + ' ' * tab->space * !tab->plus)
		+ '-' * tab->neg;
	len = ft_strlen((const char *)s_num);
	if (is_int && (tab->dash || tab->zero) && !after)
		return (write(1, &c, 1 * (tab->neg || tab->plus || tab->space)));
	if (after)
	{
		if (is_int && (!tab->zero))
			i += write(1, &c, 1 * (tab->neg || tab->plus || tab->space));
		i += write(1, s_num, len);
	}
	return (i);
}

int	ft_print_int(t_print *tab)
{
	long long	num;
	char		*s_num;
	char		c;

	num = (long long)va_arg(tab->args, int);
	tab->neg = (num < 0);
	s_num = ft_itoa(num * (-1 + 2 * !tab->neg));
	if (!s_num)
		return (free_all(tab, 0) * 0);
	s_num = make_patted_num(tab, s_num, num);
	if (!s_num)
		return (0);
	tab->printed += print_front_sign(tab, 0, s_num, 1);
	if (tab->dash)
		tab->printed += write(1, s_num, (int)ft_strlen(s_num));
	c = '0' * tab->zero * !tab->dash * !tab->precision
		+ ' ' * (tab->dash || !tab->zero || tab->precision);
	while (tab->printed < tab->width - !tab->dash * (int)ft_strlen(s_num)
		- ((tab->neg || tab->plus || tab->space) && !tab->dash && !tab->zero))
		tab->printed += write(1, &c, 1);
	if (!tab->dash)
		tab->printed += print_front_sign(tab, 1, s_num, 1);
	return (1 + free_all(tab, 1, s_num));
}

int	ft_print_uint(t_print *tab)
{
	unsigned int	num;
	char			*s_num;
	int				len;
	char			c;

	num = va_arg(tab->args, unsigned int);
	s_num = ft_itoa(num);
	if (!s_num)
		return (free_all(tab, 0) * 0);
	s_num = make_patted_num(tab, s_num, (long long)num);
	if (!s_num)
		return (0);
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

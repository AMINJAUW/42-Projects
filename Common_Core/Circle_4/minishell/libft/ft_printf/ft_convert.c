/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:31:12 by vvalet            #+#    #+#             */
/*   Updated: 2023/06/13 11:06:33 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_convert(va_list list, char key)
{
	int	count;

	count = 0;
	if (key == 'c')
		count = ft_putchar_value_fd(va_arg(list, int), 1);
	else if (key == 's')
		count = ft_putstr_value_fd(va_arg(list, char *), 1);
	else if (key == 'p')
		count = ft_putmem_hex_fd(va_arg(list, long), 1);
	else if (key == 'd' || key == 'i')
		count = ft_putnbr_value_fd(va_arg(list, int), 1);
	else if (key == 'u')
		count = ft_putui_fd(va_arg(list, int), 1);
	else if (key == 'x')
		count = ft_putui_hex_fd(va_arg(list, int), 0, 1);
	else if (key == 'X')
		count = ft_putui_hex_fd(va_arg(list, int), 1, 1);
	else if (key == '%')
		count = ft_putchar_value_fd('%', 1);
	else
		count = write(1, &key, 1);
	return (count);
}

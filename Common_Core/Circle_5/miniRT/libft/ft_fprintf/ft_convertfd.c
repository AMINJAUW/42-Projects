/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convertfd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:31:12 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/10 15:56:18 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_convertfd(va_list list, char key, int fd)
{
	int	count;

	count = 0;
	if (key == 'c')
		count = ft_putchar_value_fd(va_arg(list, int), fd);
	else if (key == 's')
		count = ft_putstr_value_fd(va_arg(list, char *), fd);
	else if (key == 'p')
		count = ft_putmem_hex_fd(va_arg(list, long), fd);
	else if (key == 'd' || key == 'i')
		count = ft_putnbr_value_fd(va_arg(list, int), fd);
	else if (key == 'u')
		count = ft_putui_fd(va_arg(list, int), fd);
	else if (key == 'x')
		count = ft_putui_hex_fd(va_arg(list, int), 0, fd);
	else if (key == 'X')
		count = ft_putui_hex_fd(va_arg(list, int), 1, fd);
	else if (key == '%')
		count = ft_putchar_value_fd('%', fd);
	else
		count = write(fd, &key, fd);
	return (count);
}

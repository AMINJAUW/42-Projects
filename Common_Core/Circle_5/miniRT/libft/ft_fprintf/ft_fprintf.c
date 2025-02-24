/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:54:32 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/10 15:56:18 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fprintf(int fd, const char *s, ...)
{
	va_list	list;
	size_t	index;
	int		count;
	int		check;

	index = 0;
	count = 0;
	va_start(list, s);
	while (s[index])
	{
		if (s[index] == '%')
		{
			index++;
			check = ft_convertfd(list, s[index], fd);
		}
		else
			check = write(fd, &s[index], 1);
		if (check == -1)
			return (-1);
		count += check;
		index++;
	}
	va_end(list);
	return (count);
}

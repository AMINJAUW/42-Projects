/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_value_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:38:53 by vvalet            #+#    #+#             */
/*   Updated: 2023/06/06 14:13:02 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putstr_value_fd(char *s, int fd)
{
	size_t	index;

	if (!s)
	{
		if (write(fd, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	index = 0;
	while (s[index])
	{
		if (write(fd, &s[index], 1) == -1)
			return (-1);
		index++;
	}
	return (index);
}

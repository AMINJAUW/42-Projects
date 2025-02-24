/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:16:58 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/09 12:55:20 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*last;

	str = (char *)s;
	last = 0;
	while (*str)
	{
		if (*str == (char)c)
			last = str;
		str ++;
	}
	if (*str == (char)c)
		return (str);
	else if (last == 0)
		return (0);
	return (last);
}

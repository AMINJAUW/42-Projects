/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:47:48 by aminjauw          #+#    #+#             */
/*   Updated: 2023/09/22 12:57:25 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoins(size_t str_nbr, ...)
{
	va_list	string;
	char	*joined;
	char	*s1;
	size_t	i;

	va_start(string, str_nbr);
	if (str_nbr == 1)
		return (ft_strdup(va_arg(string, char *)));
	joined = va_arg(string, char *);
	i = 1;
	while (i < str_nbr && joined != NULL)
	{
		s1 = joined;
		joined = ft_strjoin(joined, va_arg(string, char *));
		if (i != 1)
			free(s1);
		i++;
	}
	return (joined);
}

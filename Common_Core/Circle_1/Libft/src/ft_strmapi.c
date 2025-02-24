/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:50:06 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/09 11:49:31 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*init_str;
	char			*str;
	unsigned int	len;
	unsigned int	i;

	if (!s || !f)
		return (0);
	init_str = (char *)s;
	len = (unsigned int) ft_strlen(init_str);
	str = malloc(sizeof(char) * (1 + len));
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = (*f)(i, init_str[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}

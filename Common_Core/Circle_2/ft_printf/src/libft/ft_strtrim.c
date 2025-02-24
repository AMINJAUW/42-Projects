/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:22:45 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/14 12:11:01 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char const *s1, char const *set, int direction)
{
	size_t	len;
	size_t	i;
	size_t	j;
	int		out;

	out = 0;
	len = ft_strlen(s1);
	i = 0;
	if (direction < 0)
		i = len - 1;
	while (i < len && i >= 0)
	{
		j = 0;
		while (set[j] != 0 && set[j] != s1[i])
			j++;
		if (set[j] == 0)
			break ;
		else
			out ++;
		i = i + direction;
	}
	return (out);
}

static void	chec_nbr(char const *s1, int *f, int *b)
{
	int	len;

	len = (int)ft_strlen(s1);
	if (*f + *b > len)
	{
		*f = len;
		*b = 0;
	}
	return ;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		len;
	int		nbrf;
	int		nbrb;
	int		i;

	if (!s1 || !set)
		return (0);
	nbrf = count(s1, set, 1);
	nbrb = count(s1, set, -1);
	chec_nbr(s1, &nbrf, &nbrb);
	len = (int)ft_strlen((char *)s1);
	str = malloc(sizeof(char) * (1 + len - nbrf - nbrb));
	if (!str)
		return (0);
	i = 0;
	while (i + nbrf < len - nbrb)
	{
		str[i] = s1[i + nbrf];
		i++;
	}
	str[i] = 0;
	return (str);
}

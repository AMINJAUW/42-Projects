/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:44:07 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/21 11:37:33 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*pwd;
	size_t	i;

	i = 0;
	pwd = malloc(nmemb * size);
	if (! pwd)
		return (0);
	while (i < nmemb * size)
	{
		pwd[i] = 0;
		i ++;
	}
	return (pwd);
}

char	*ft_str_cat_char(char *s1, char *buffer, int j)
{
	char	*str;
	size_t	i;
	int		len;

	len = 0;
	if (s1)
		len = ft_strlen(s1);
	str = malloc(sizeof(char) * (2 + len));
	if (!str)
		return (free_all(s1));
	i = 0;
	while (s1 && s1[i] != 0)
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = buffer[j];
	str[i] = 0;
	if (s1)
		free(s1);
	buffer[j] = 0;
	return (str);
}

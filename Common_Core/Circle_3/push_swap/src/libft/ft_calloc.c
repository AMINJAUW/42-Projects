/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:39:55 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/07 15:47:30 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

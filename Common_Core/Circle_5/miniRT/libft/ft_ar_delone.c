/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ar_delone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:08:44 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/09 13:19:09 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ar_delone(char ***ar, size_t index)
{
	size_t	size;
	char	**new_ar;
	size_t	i;
	int		j;

	size = ft_ar_len(*ar);
	new_ar = (char **)ft_calloc(size, sizeof(char *));
	if (new_ar == NULL)
		return (1);
	i = 0;
	j = 0;
	while (i <= size)
	{
		if (i != index)
			new_ar[i + j] = (*ar)[i];
		else
		{
			j--;
			free((*ar)[i]);
		}
		i++;
	}
	free(*ar);
	*ar = new_ar;
	return (0);
}

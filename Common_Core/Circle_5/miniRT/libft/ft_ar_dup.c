/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ar_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:54:37 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/09 13:18:55 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_ar_dup(char **ar)
{
	char	**new_ar;
	int		i;

	new_ar = (char **)ft_calloc(ft_ar_len(ar) + 1, sizeof(char *));
	if (new_ar == NULL)
		return (NULL);
	i = 0;
	while (ar[i])
	{
		new_ar[i] = ft_strdup(ar[i]);
		if (new_ar[i] == NULL)
		{
			ft_ar_clear(&new_ar);
			return (NULL);
		}
		i++;
	}
	new_ar[i] = NULL;
	return (new_ar);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ardup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:54:37 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/05 12:29:42 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_ardup(char **ar)
{
	char	**new_ar;
	int		i;

	new_ar = (char **)ft_calloc(ft_arlen(ar) + 1, sizeof(char *));
	if (new_ar == NULL)
		return (NULL);
	i = 0;
	while (ar[i])
	{
		new_ar[i] = ft_strdup(ar[i]);
		if (new_ar[i] == NULL)
		{
			ft_arclear(&new_ar);
			return (NULL);
		}
		i++;
	}
	new_ar[i] = NULL;
	return (new_ar);
}

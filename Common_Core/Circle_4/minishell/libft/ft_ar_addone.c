/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ar_addone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:08:44 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/02 14:13:05 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ar_addone(char ***ar, char *s)
{
	char	**new_ar;
	size_t	i;

	new_ar = (char **)ft_calloc(ft_arlen(*ar) + 2, sizeof(char *));
	if (new_ar == NULL)
		return (1);
	i = 0;
	while (i < ft_arlen(*ar))
	{
		new_ar[i] = (*ar)[i];
		i++;
	}
	new_ar[i] = ft_strdup(s);
	if (new_ar[i] == NULL)
		return (1);
	new_ar[i + 1] = NULL;
	free(*ar);
	*ar = new_ar;
	return (0);
}

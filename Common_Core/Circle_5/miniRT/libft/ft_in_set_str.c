/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_set_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:10:47 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/19 14:52:56 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_in_set_str(char *s, char **set)
{
	if (s == NULL || set == NULL)
		return (FALSE);
	while (*set)
	{
		if (ft_strncmp(s, *set, ft_strlen(s) + 1))
			return (TRUE);
		set++;
	}
	return (FALSE);
}

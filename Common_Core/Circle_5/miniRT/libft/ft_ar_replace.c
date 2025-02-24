/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ar_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:08:44 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/09 13:16:58 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ar_replace(char **ar, size_t index, char *s)
{
	char	*new_str;

	new_str = ft_strdup(s);
	if (new_str == NULL)
		return (1);
	free(ar[index]);
	ar[index] = new_str;
	return (0);
}

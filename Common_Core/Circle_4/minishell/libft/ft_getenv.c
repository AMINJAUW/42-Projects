/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:55:43 by vvalet            #+#    #+#             */
/*   Updated: 2023/09/12 14:18:24 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name, char **envp)
{
	char	*value;
	size_t	size;

	size = ft_strlen(name);
	while (*envp && (ft_strncmp(name, *envp, size) != 0
			|| ft_strncmp("=", &(*envp)[size], 1) != 0))
		envp++;
	value = *envp;
	if (value && *value)
		value += size + 1;
	return (value);
}

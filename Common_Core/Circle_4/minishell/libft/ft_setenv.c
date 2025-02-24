/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:55:43 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/03 14:50:27 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setenv(char *name, char *value, char **envp)
{
	size_t	size;
	char	*new_variable;
	size_t	index;

	size = ft_strlen(name);
	while (*envp && (ft_strncmp(name, *envp, size) != 0
			|| ft_strncmp("=", &(*envp)[size], 1) != 0))
		envp++;
	if (*envp)
	{
		if (value != NULL)
			size = ft_strlen(name) + ft_strlen(value) + 2;
		else
			size = ft_strlen(name) + 2;
		new_variable = (char *)ft_calloc(size, sizeof(char));
		if (new_variable == NULL)
			return (FAIL);
		index = ft_strlcpy(new_variable, name, ft_strlen(name) + 1);
		index += ft_strlcpy(&new_variable[index], "=", 2);
		if (value != NULL)
			ft_strlcpy(&new_variable[index], value, ft_strlen(value) + 1);
		free(*envp);
		*envp = new_variable;
	}
	return (SUCCES);
}

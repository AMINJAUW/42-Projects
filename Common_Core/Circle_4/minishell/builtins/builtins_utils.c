/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:54:40 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/04 13:28:21 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_index(char *s, char **envp)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[size] != '\0' && s[size] != '=')
		size++;
	while (envp[i])
	{
		if (ft_strncmp(s, envp[i], size) == 0
			&& (envp[i][size] == '=' || envp[i][size] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	str_is_num(char *str)
{
	while (*str && ft_isspace(*str) == TRUE)
		str++;
	if (*str == 0)
		return (FALSE);
	if (*str == '+' || *str == '-')
		str++;
	while (*str && ft_isspace(*str) == FALSE)
	{
		if (ft_isdigit(*str) == 0)
			return (FALSE);
		str++;
	}
	while (*str && ft_isspace(*str) == TRUE)
		str++;
	if (*str != 0)
		return (FALSE);
	return (TRUE);
}

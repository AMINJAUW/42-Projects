/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_declare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:30:26 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/02 14:05:54 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*next_var(char *current, char **envp)
{
	int		i;
	char	*next;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], current, ft_strlen(envp[i])) <= 0)
		i++;
	next = envp[i];
	while (envp[i])
	{
		if (ft_strncmp(envp[i], current, ft_strlen(envp[i])) > 0
			&& ft_strncmp(envp[i], next, ft_strlen(envp[i])) < 0)
			next = envp[i];
		i++;
	}
	return (next);
}

static void	display_line(char *ptr)
{
	write (1, "declare -x ", 11);
	while (*ptr && *ptr != '=')
	{
		write (1, ptr, 1);
		ptr++;
	}
	if (*ptr == '=')
	{
		write (1, "=\"", 2);
		ptr++;
		while (*ptr)
		{
			write (1, ptr, 1);
			ptr++;
		}
		write (1, "\"", 1);
	}
	write (1, "\n", 1);
}

void	declare(int argc, char **envp)
{
	size_t	i;
	char	*ptr;

	if (argc != 1)
		return ;
	i = 0;
	ptr = next_var("\0", envp);
	while (i < ft_arlen(envp))
	{
		display_line(ptr);
		ptr = next_var(ptr, envp);
		i++;
	}
}

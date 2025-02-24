/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:35:23 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/04 16:30:52 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns TRUE if the index starts at a $ and that the last char before that is
not a space, is a redirection. Else, returns FALSE. */
int	is_io(char *line, int index)
{
	int	i;
	int	io;

	i = 0;
	io = FALSE;
	while (i <= index)
	{
		if (ft_isspace(line[i]) == TRUE || line[i] == '|')
		{
			io = FALSE;
			i++;
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			io = TRUE;
			i++;
			while (i <= index && ft_isspace(line[i]) == TRUE)
				i++;
		}
		else
			i++;
	}
	return (io);
}

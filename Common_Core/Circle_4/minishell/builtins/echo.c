/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:14:32 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/02 14:05:45 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option_n(char *str)
{
	if (*str != '-')
		return (FALSE);
	else
		str++;
	while (*str)
	{
		if (*str != 'n')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int	ft_echo(int argc, char **argv, t_data *data)
{
	int	n_arg;
	int	i;

	(void)data;
	(void)argc;
	n_arg = FALSE;
	i = 1;
	while (argv[i] && is_option_n(argv[i]) == TRUE)
	{
		n_arg = TRUE;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (n_arg == FALSE)
		printf("\n");
	return (SUCCES);
}

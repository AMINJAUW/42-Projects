/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:14:32 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/02 14:59:25 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_validity(char *s)
{
	if (ft_isalpha(*s) == FALSE && *s != '_')
		return (FALSE);
	while (*s)
	{
		if (ft_isalnum(*s) == FALSE && *s != '_')
			return (FALSE);
		s++;
	}
	return (TRUE);
}

int	ft_unset(int argc, char **argv, t_data *data)
{
	int	i;
	int	index;

	(void)argc;
	i = 1;
	while (argv[i])
	{
		if (check_validity(argv[i]) == FALSE)
		{
			ft_error(1, argv[i], WRONGID_STR, data);
			i++;
			continue ;
		}
		index = find_index(argv[i], data->envp);
		if (index != -1 && ft_ar_delone(&data->envp, index) == FAIL)
			return (ft_error(errno, NULL, NULL, data));
		i++;
	}
	return (SUCCES);
}

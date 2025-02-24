/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:14:32 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/04 14:23:58 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(int argc, char **argv, t_data *data)
{
	int	i;

	(void)argc;
	(void)argv;
	i = 0;
	while (data->envp[i])
	{
		if (ft_char_count(data->envp[i], '=') > 0)
			printf("%s\n", data->envp[i]);
		i++;
	}
	return (SUCCES);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:22:40 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/13 10:16:08 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(int argc, char **argv, t_data *data)
{
	if (data->commands->next == NULL)
	{
		data->err_nbr = data->last_err;
		dup2(data->saved_tty_fds[1], STDOUT_FILENO);
		printf("exit\n");
	}
	if (argc > 2 && str_is_num(argv[1]) == TRUE)
		return (ft_error(1, NULL, TOO_MANY_ARGS, data));
	else if (argc > 1 && str_is_num(argv[1]) == FALSE)
	{
		data->exit_flag = 1;
		return (ft_error(255, argv[1], NON_NUM_ARGS, data));
	}
	if (argc == 2 && str_is_num(argv[1]) == TRUE)
		data->err_nbr = ft_atoi(argv[1]);
	data->exit_flag = 1;
	return (SUCCES);
}

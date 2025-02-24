/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:01:27 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/13 12:25:37 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_line(t_data *data)
{
	if (g_sig_flag == SIGINT)
	{
		data->err_nbr = 1;
		data->last_err = data->err_nbr;
	}
	if (data->line == NULL && errno == 0)
	{
		if (data->exit_flag != SINGLE_LINE)
			printf("exit\n");
		data->err_nbr = data->last_err;
		data->exit_flag = TRUE;
	}
	else if (data->line == NULL && errno != 0)
		ft_error(errno, NULL, NULL, data);
	else if (ft_strncmp(data->line, "", 1) == 0)
		data->err_nbr = data->last_err;
	return (data->err_nbr);
}

void	check_signal_exec(t_data *data)
{
	(void)data;
	if (g_sig_flag == SIGINT && data->cur_cmd != NULL)
		printf("\n");
	if (g_sig_flag == SIGQUIT)
		printf("Quit: 3\n");
}

void	sig_exec(int sig)
{
	g_sig_flag = sig;
}

void	sigint_prompt(int sig)
{
	(void)sig;
	g_sig_flag = SIGINT;
	ioctl(0, TIOCSTI, "\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:38:35 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/13 09:55:49 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_line(t_data *data)
{
	if (check_line(data) != 0 || data->exit_flag == TRUE)
		return ;
	data->final_line = ft_strdup(data->line);
	if (data->final_line == NULL)
	{
		ft_error(errno, NULL, NULL, data);
		return ;
	}
	lexer(data);
	parser(data);
	finish_parsing(data);
	if (ft_strncmp(data->final_line, "", 1) != 0)
		add_history(data->final_line);
	if (g_sig_flag == 0)
	{
		signal(SIGINT, sig_exec);
		signal(SIGQUIT, sig_exec);
		executer(data);
	}
	check_signal_exec(data);
}

int	main(int argc, char **argv, char **envp)
{
	static t_data	data = {0};

	(void) argv;
	if (argc != 1)
		return (printf("minishell: no arguments needed here\n"));
	init_env(envp, &data);
	if (isatty(STDIN_FILENO) == FALSE)
	{
		errno = 0;
		data.exit_flag = SINGLE_LINE;
		data.line = get_next_line(STDIN_FILENO);
		run_line(&data);
		data.exit_flag = TRUE;
	}
	while (data.exit_flag == FALSE)
	{
		clear_data(&data);
		data.line = readline("\x1b[32m\x1b[1mminishell: \x1b[0m");
		run_line(&data);
	}
	close_env(&data);
}

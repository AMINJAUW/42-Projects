/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mgmt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:21:53 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/10 10:33:40 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_shlvl(t_data *data)
{
	int		shlvl;
	char	*value;

	if (ft_getenv("SHLVL", data->envp) == NULL)
		shlvl = 1;
	else
		shlvl = ft_atoi(ft_getenv("SHLVL", data->envp)) + 1;
	value = ft_itoa(shlvl);
	if (value == NULL)
		return (FAIL);
	if (ft_setenv("SHLVL", value, data->envp) == FAIL)
	{
		ft_free((void **)&value);
		return (FAIL);
	}
	else
	{
		ft_free((void **)&value);
		return (SUCCES);
	}
}

void	init_env(char **envp, t_data *data)
{
	g_sig_flag = 0;
	data->last_err = 0;
	data->exit_flag = 0;
	rl_catch_signals = 0;
	data->line = NULL;
	data->final_line = NULL;
	data->exp_tab = NULL;
	data->lex_line = NULL;
	data->lex_tab = NULL;
	data->commands = NULL;
	data->cur_cmd = NULL;
	data->exec_path = NULL;
	data->oldcwd = NULL;
	data->cwd = getcwd(NULL, 0);
	data->envp = ft_ardup(envp);
	if (data->envp == NULL || data->cwd == NULL
		|| update_shlvl(data) == FAIL || save_tty_fds(data) == FAIL)
	{
		ft_error(errno, NULL, NULL, data);
		close_env(data);
		exit(data->err_nbr);
	}
}

void	clear_data(t_data *data)
{
	ft_free((void **)&data->line);
	ft_free((void **)&data->final_line);
	ft_free((void **)&data->exp_tab);
	ft_free((void **)&data->lex_line);
	ft_free((void **)&data->lex_tab);
	while (data->commands != NULL)
		commands_free_first(data);
	data->cur_cmd = NULL;
	data->trailing_pipe = FALSE;
	ft_arclear(&data->exec_path);
	data->exec_path = NULL;
	data->last_err = data->err_nbr;
	data->err_nbr = 0;
	errno = 0;
	g_sig_flag = 0;
	signal(SIGINT, sigint_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	close_env(t_data *data)
{
	clear_data(data);
	if (data->saved_tty_fds[0] != 0)
		close(data->saved_tty_fds[0]);
	if (data->saved_tty_fds[1] != 0)
		close(data->saved_tty_fds[1]);
	ft_arclear(&data->envp);
	ft_free((void **)&data->oldcwd);
	ft_free((void **)&data->cwd);
	rl_clear_history();
	exit (data->last_err);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_mgmt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:27:23 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/06 09:09:03 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	int			i;
	static char	names[7][7]
		= {"cd", "echo", "env", "exit", "export", "pwd", "unset"};

	i = 0;
	while (i < 7 && ft_strncmp(cmd, names[i], ft_strlen(names[i]) + 1) != 0)
		i++;
	return (i < 7);
}

void	find_builtin(char *cmd, int (**fct)(int, char**, t_data*))
{
	int			i;
	static char	names[7][7]
		= {"cd", "echo", "env", "exit", "export", "pwd", "unset"};
	static int	(*builtin[7])(int, char**, t_data*)
		= {ft_cd, ft_echo, ft_env, ft_exit, ft_export, ft_pwd, ft_unset};

	i = 0;
	while (i < 7 && ft_strncmp(cmd, names[i], ft_strlen(names[i]) + 1) != 0)
		i++;
	if (i < 7)
		*fct = builtin[i];
	else
		*fct = NULL;
}

void	fd_management_builtin(t_cmd *command, t_data *data)
{
	close_fd_secure(command->input_fd, data);
	if (command->output_fd != STDOUT_FILENO)
		dup2(command->output_fd, STDOUT_FILENO);
	close_fd_secure(command->output_fd, data);
	data->cur_cmd = command->command_line[0];
}

void	run_builtin(t_data *data, t_cmd *command)
{
	int	(*builtins)(int, char**, t_data*);

	find_builtin(command->command_line[0], &builtins);
	builtins(ft_arlen(command->command_line),
		command->command_line, data);
}

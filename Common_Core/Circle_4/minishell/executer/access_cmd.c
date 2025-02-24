/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:28:41 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/04 15:44:17 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_cmd_path(t_data *data, t_cmd *commands)
{
	if (access(commands->command_line[0], X_OK) == 0)
	{
		commands->cmd_path = ft_strdup(commands->command_line[0]);
		if (commands->cmd_path == NULL)
			return (ft_error(errno, NULL, NULL, data));
		return (SUCCES); 
	}
	else if (access(commands->command_line[0], F_OK) == 0)
		return (ft_error(126, NULL, PERMISSION_STR, data));
	else
		return (ft_error(127, NULL, NO_FILE_STR, data));
}

static int	not_only_dots(t_data *data, t_cmd *commands)
{
	int	i;

	if (ft_strncmp(commands->command_line[0], ".", 2) == SUCCES)
		return (ft_error(2, NULL, ONLY_DOTS, data));
	i = 0;
	while (commands->command_line[0][i] != '\0')
	{
		if (commands->command_line[0][i] != '.')
			return (SUCCES);
		i++;
	}
	if (no_path(data))
		return (ft_error(127, NULL, NO_FILE_STR, data));
	return (ft_error(CMD_NOT_FOUND, NULL,
			CMD_NOT_FOUND_STR, data));
}

static int	set_absolute_cmd_path(t_data *data, t_cmd *commands)
{
	int	i;
	int	file_exist;

	file_exist = FALSE;
	i = 0;
	while (data->exec_path[i] != NULL)
	{
		commands->cmd_path = ft_strjoins(3, data->exec_path[i],
				"/", commands->command_line[0]);
		if (commands->cmd_path == NULL)
			return (ft_error(errno, NULL, NULL, data));
		if (access(commands->cmd_path, X_OK) == SUCCES)
			break ;
		if (access(commands->cmd_path, F_OK) == SUCCES)
			file_exist = TRUE;
		ft_free((void **)&commands->cmd_path);
		i++;
	}
	if (data->exec_path[i] == NULL && file_exist)
		return (ft_error(126, NULL,
				PERMISSION_STR, data));
	else if (data->exec_path[i] == NULL)
		return (ft_error(127, NULL,
				CMD_NOT_FOUND_STR, data));
	return (SUCCES);
}

static int	check_if_dir(t_data *data, t_cmd *commands)
{
	DIR	*dir;

	dir = opendir(commands->command_line[0]);
	if (dir == NULL)
	{
		if (errno == ENOTDIR || errno == ENOENT)
			return (SUCCES);
		else if (errno == EACCES
			&& is_path_cmd(commands->command_line[0]) == TRUE)
			return (ft_error(126, NULL, DIRECTORY_STR, data));
		else
			return (ft_error(errno, NULL, NULL, data));
	}
	closedir(dir);
	if (is_path_cmd(commands->command_line[0]) == TRUE)
		return (ft_error(126, NULL, DIRECTORY_STR, data));
	return (SUCCES);
}

int	access_command(t_data *data, t_cmd *commands)
{
	if (not_only_dots(data, commands) == FAIL)
		return (FAIL);
	if (check_if_dir(data, commands) == FAIL)
		return (FAIL);
	if (no_path(data) || is_path_cmd(commands->command_line[0]))
		return (set_cmd_path(data, commands));
	if (set_absolute_cmd_path(data, commands) == FAIL)
		return (FAIL);
	return (SUCCES);
}

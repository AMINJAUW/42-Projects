/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:14:32 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/13 12:04:20 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_path(char **temp, char *param)
{
	if (*temp == NULL)
		*temp = param;
	else if (ft_strncmp(*temp, "//", 2) == 0)
		printf("%s\n", (*temp) + 1);
	else
		printf("%s\n", *temp);
}

static char	*find_path(char *param, char **envp)
{
	char		**cdpath;
	int			i;
	char		*temp;
	struct stat	datas;

	if (ft_in_set_char(param[0], "./") == TRUE
		|| ft_getenv("CDPATH", envp) == NULL)
		return (param);
	cdpath = ft_split(ft_getenv("CDPATH", envp), ':');
	if (cdpath == NULL)
		return (NULL);
	i = 0;
	while (cdpath[i])
	{
		temp = ft_strjoins(3, cdpath[i], "/", param);
		if (temp == NULL)
			return (NULL);
		if (stat(temp, &datas) == SUCCES && S_ISDIR(datas.st_mode) == TRUE)
			break ;
		ft_free((void **)&temp);
		i++;
	}
	handle_path(&temp, param);
	ft_arclear(&cdpath);
	return (temp);
}

static int	change_directory(char *path, char **envp, t_data *data)
{
	int		error;

	error = 0;
	if (ft_getenv("OLDPWD", envp) != NULL
		&& ft_setenv("OLDPWD", data->cwd, envp) == FAIL)
		return (ft_error(errno, NULL, NULL, data));
	ft_free((void **)&data->oldcwd);
	data->oldcwd = ft_strdup(data->cwd);
	if (data->oldcwd == NULL)
		return (ft_error(errno, NULL, NULL, data));
	if (chdir(path) == -1)
		return (ft_error(errno, path, NULL, data));
	ft_free((void **)&data->cwd);
	data->cwd = getcwd(NULL, 0);
	if (data->cwd == NULL)
	{
		data->cwd = ft_strjoin(data->oldcwd, "/..");
		if (data->oldcwd == NULL)
			return (ft_error(errno, NULL, NULL, data));
		ft_error(0, NULL, PARENT_DIR_STR, data);
	}
	if (ft_getenv("PWD", envp) != NULL 
		&& ft_setenv("PWD", data->cwd, envp) == FAIL)
		return (ft_error(errno, NULL, NULL, data));
	return (error);
}

int	ft_cd(int argc, char **argv, t_data *data)
{
	char	*path;

	if (argc == 1 && ft_getenv("HOME", data->envp) == NULL)
		return (ft_error(1, NULL, HOME_NOT_SET_STR, data));
	if ((argc == 1 && ft_strncmp(ft_getenv("HOME", data->envp), "", 2) == 0)
		|| (argc != 1 && argv[1][0] == 0))
		return (SUCCES);
	else if (argc == 1)
		path = ft_getenv("HOME", data->envp);
	else
		path = find_path(argv[1], data->envp);
	if (path == NULL)
		return (ft_error(errno, NULL, NULL, data));
	if (change_directory(path, data->envp, data) == FAIL)
		return (FAIL);
	if (argc != 1 && path != argv[1])
		ft_free((void **)&path);
	return (SUCCES);
}

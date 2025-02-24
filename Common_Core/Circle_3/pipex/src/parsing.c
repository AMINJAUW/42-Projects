/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:15:41 by aminjauw          #+#    #+#             */
/*   Updated: 2025/02/24 16:11:06 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	**make_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_memcmp(env[i], "PATH=", 5 * sizeof(char)))
			break ;
		i++;
	}
	return (ft_split(env[i] + 5, ':'));
}

int	fill_arr(char	***arr, char **path, char **av)
{
	int		i;
	int		j;
	char	*t;

	j = -1;
	while (++j < arr_len(path))
	{
		arr[j] = ft_calloc(sizeof(char **), (arr_len(av) + 1));
		if (malloc_error(arr[j], 3, 2, path, 2, av, 3, arr))
			return (0);
		t = ft_strjoin(path[j], "/");
		if (malloc_error(t, 4, 2, path, 2, av, 3, arr, 1, t))
			return (0);
		arr[j][0] = ft_strjoin(t, av[0]);
		if (!free_a(1, t) && malloc_error(arr[j][0], 3, 2, path, 2, av, 3, arr))
			return (0);
		i = 0;
		while (++i < arr_len(av))
		{
			arr[j][i] = ft_strdup(av[i]);
			if (malloc_error(arr[j][i], 3, 2, path, 2, av, 3, arr))
				return (0);
		}
	}
	return (1);
}

char	***make_array(char **path, char *av_str)
{
	char	***arr;
	int		argc;
	char	**av;

	av = arg_split(av_str);
	if (malloc_error(path, 0) || malloc_error(av, 1, 2, path))
		return (0);
	argc = arr_len(av);
	arr = ft_calloc(sizeof(char ***), (argc + 1));
	if (malloc_error(arr, 2, 2, path, 2, av))
		return (0);
	if (!fill_arr(arr, path, av))
	{
		free_arr(2, (void **)path);
		free_arr(2, (void **)av);
		return (NULL);
	}
	return (arr + free_arr(2, (void **)path) + free_arr(2, (void **)av));
}

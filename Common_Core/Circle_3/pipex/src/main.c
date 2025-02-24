/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:28:48 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/31 13:31:40 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_perror(char *str)
{
	perror(str);
	return (0);
}

int	multiple_dup2(int n, ...)
{
	va_list	arg;
	int		i;

	i = 0;
	va_start(arg, n);
	while (i < n)
	{
		if (-1 == dup2(va_arg(arg, int), va_arg(arg, int)))
			exit(5 + ft_perror("Problem with dup2()"));
		i++;
	}
	return (0);
}

void	ft_exec(char ***arr, char **env)
{
	int	i;

	i = 0;
	while (arr[i] && access(arr[i][0], X_OK) == -1)
	{
		i++;
	}
	if (!arr[i])
		exit(5 + ft_perror("Problems with Command given"));
	execve(arr[i][0], arr[i], env);
}

void	child(char ****arr, char **argv, char **env)
{
	int	fd[2];
	int	id;
	int	p_fd[2];

	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd[0] < 0 || fd[1] < 0)
		exit(2 + ft_perror("Problems with files given"));
	if (pipe(p_fd))
		exit(3 + ft_perror("Problems with pipe making"));
	multiple_dup2(2, fd[0], STDIN_FILENO, p_fd[1], STDOUT_FILENO);
	close_mult(2, fd[0], p_fd[1]);
	id = fork();
	if (id < 0)
		exit(4 + ft_perror("Problems with fork"));
	if (id == 0)
	{
		close_mult(2, fd[1], p_fd[0]);
		ft_exec(arr[0], env);
	}
	wait(NULL);
	multiple_dup2(2, p_fd[0], STDIN_FILENO, fd[1], STDOUT_FILENO);
	close_mult(2, fd[1], p_fd[0]);
	ft_exec(arr[1], env);
}

int	main(int argc, char **argv, char **env)
{
	char	***arr[3];
	int		id;

	if (argc != 5)
	{
		perror("Wrong number of args");
		exit(4);
	}
	arr[0] = make_array(make_paths(env), argv[2]);
	if (!arr[0])
		return (6);
	arr[1] = make_array(make_paths(env), argv[3]);
	if (arr[1] == NULL)
		return (5 + free_arr(3, (void **)arr[1]));
	id = fork();
	if (id < 0)
		exit(4 + ft_perror("Problems with fork"));
	if (id == 0)
		child(arr, argv, env);
	wait(NULL);
	free_arr(3, (void **)arr[0]);
	free_arr(3, (void **)arr[1]);
	return (0);
}

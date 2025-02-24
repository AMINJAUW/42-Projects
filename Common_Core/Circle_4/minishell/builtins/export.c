/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:14:32 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/06 09:09:56 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_method(char *s)
{
	if (ft_isalpha(*s) == FALSE && *s != '_')
		return (FALSE);
	while (*s && *s != '=')
	{
		if ((*s == '+' && *(s + 1) && *(s + 1) != '=')
			&& (ft_isalnum(*s) == FALSE && *s != '_'))
			return (FALSE);
		s++;
	}
	if (*s == '=' && *(s - 1) == '+')
		return (2);
	else
		return (1);
}

static int	ft_ar_append(char **ar, size_t index, char *s)
{
	char	*str;

	str = ft_strjoin(ar[index], ft_strchr(s, '=') + 1);
	if (str == NULL)
		return (FAIL);
	if (ft_ar_replace(ar, index, str) == FAIL)
		return (FAIL);
	free(str);
	return (SUCCES);
}

static int	export_variable(char *arg, t_data *data)
{
	int	error;
	int	method;
	int	index;

	error = 0;
	method = check_method(arg);
	if (method == 2)
		ft_memmove(ft_strnstr(arg, "+=", ft_strlen(arg)),
			ft_strnstr(arg, "+=", ft_strlen(arg)) + 1,
			ft_strlen(ft_strnstr(arg, "+=", ft_strlen(arg))));
	index = find_index(arg, data->envp);
	if (index == -1)
		error = ft_ar_addone(&data->envp, arg);
	else if (method == 1)
		error = ft_ar_replace(data->envp, index, arg);
	else
		error = ft_ar_append(data->envp, index, arg);
	if (error != 0)
		return (ft_error(errno, NULL, NULL, data));
	return (SUCCES);
}

int	ft_export(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	declare(argc, data->envp);
	while (argv[i])
	{
		if (check_method(argv[i]) == FALSE)
		{
			ft_error(1, argv[i], WRONGID_STR, data);
			i++;
			continue ;
		}
		else if (export_variable(argv[i], data) == FAIL)
			return (FAIL);
		i++;
	}
	return (SUCCES);
}

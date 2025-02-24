/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:56:32 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/06 13:02:24 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_trailing_pipe(t_data *data)
{
	int	len;

	len = 0;
	while (data->lex_line[len])
		len++;
	if (is_pipe(data, len - 1))
		data->trailing_pipe = TRUE;
	else
		data->trailing_pipe = FALSE;
}

int	check_io(t_data *data)
{
	int	i;

	i = 0;
	while (data->lex_line[i] != NULL)
	{
		if (is_chevrons(data, i))
		{
			if (data->lex_line[i + 1] == NULL)
				return (ft_error(258, "newline", TOKEN_STR, data));
			else if (is_chevrons(data, i + 1)
				|| is_pipe(data, i + 1))
				return (ft_error(258, data->lex_line[i + 1],
						TOKEN_STR, data));
		}
		if (is_pipe(data, i)
			&& (i == 0
				|| (data->lex_line[i + 1]
					&& is_pipe(data, i + 1))))
			return (ft_error(258, data->lex_line[i], TOKEN_STR, data));
		i++;
	}
	return (SUCCES);
}

void	free_unused_args(t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	while (data->lex_line[i] != NULL)
	{
		str = data->lex_line[i];
		if (is_pipe(data, i))
			ft_free((void **)&str);
		else if (is_chevrons(data, i))
			ft_free((void **)&str);
		i++;
	}
}

int	parser(t_data *data)
{
	if (data->err_nbr != SUCCES || g_sig_flag != FALSE 
		|| string_arr_empty(data->lex_line))
		return (SUCCES);
	if (check_io(data) == FAIL)
	{
		ft_arclear(&data->lex_line);
		return (FAIL);
	}
	if (mk_commands(data) == FAIL)
	{
		free_unused_args(data);
		while (data->commands != NULL)
			commands_free_first(data);
		return (FAIL);
	}
	check_trailing_pipe(data);
	free_unused_args(data);
	data->exec_path = ft_split(ft_getenv("PATH", data->envp), ':');
	if (data->exec_path == NULL && ft_getenv("PATH", data->envp) != NULL)
		return (ft_error(errno, NULL, NULL, data));
	return (SUCCES);
}

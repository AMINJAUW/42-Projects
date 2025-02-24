/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:24:56 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/05 13:11:29 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_error(int err_code, char *token, char *str, t_data *data)
{
	if (err_code != 0)
		data->err_nbr = 1;
	if (token == NULL)
		ft_fprintf(2, "%sminishell:%s %s: %s\n", RED, WHI, data->cur_cmd, str);
	else if (str == NULL)
		ft_fprintf(2, "%sminishell:%s %s: %s: %s\n", RED, WHI, data->cur_cmd,
			token, strerror(errno));
	else
		ft_fprintf(2, "%sminishell:%s %s: %s: %s\n", RED, WHI, data->cur_cmd,
			token, str);
}

static void	exp_uns_error(int err_code, char *token, char *str, t_data *data)
{
	if (err_code != 0)
		data->err_nbr = 1;
	data->err_nbr = 1;
	ft_fprintf(2, "%sminishell:%s %s: `%s': %s\n", RED, WHI, data->cur_cmd,
		token, str);
}

int	ft_error(int err_code, char *token, char *str, t_data *data)
{
	data->err_nbr = err_code;
	if (data->cur_cmd != NULL && (token != NULL || str != NULL)
		&& ft_strncmp(data->cur_cmd, "cd", 3) == 0)
		cd_error(err_code, token, str, data);
	else if (data->cur_cmd != NULL && (token != NULL || str != NULL)
		&& (ft_strncmp(data->cur_cmd, "export", 7) == 0
			|| ft_strncmp(data->cur_cmd,
				"unset", 6) == 0))
		exp_uns_error(err_code, token, str, data);
	else if (data->cur_cmd == NULL && token == NULL && str == NULL)
		ft_fprintf(2, "%sminishell:%s %s\n", RED, WHI,
			strerror(data->err_nbr));
	else if (data->cur_cmd == NULL && token == NULL && str != NULL)
		ft_fprintf(2, "%sminishell:%s %s\n", RED, WHI, str);
	else if (data->cur_cmd == NULL && token != NULL && str != NULL)
		ft_fprintf(2, "%sminishell:%s %s `%s'\n", RED, WHI, str, token);
	else if (data->cur_cmd != NULL && token == NULL && str == NULL)
		ft_fprintf(2, "%sminishell:%s %s: %s\n", RED, WHI, data->cur_cmd,
			strerror(data->err_nbr));
	else if (data->cur_cmd != NULL && token == NULL && str != NULL)
		ft_fprintf(2, "%sminishell:%s %s: %s\n", RED, WHI, data->cur_cmd, str);
	else if (data->cur_cmd != NULL && token != NULL && str != NULL)
		ft_fprintf(2, "minishell: %s: %s: %s\n", RED, WHI, data->cur_cmd,
			token, str);
	return (FAIL);
}

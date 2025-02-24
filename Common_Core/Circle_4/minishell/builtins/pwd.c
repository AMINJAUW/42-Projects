/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:14:32 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/02 14:06:00 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int argc, char **argv, t_data *data)
{
	(void)argc;
	(void)argv;
	printf("%s\n", data->cwd);
	return (SUCCES);
}

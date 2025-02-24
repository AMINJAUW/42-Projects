/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_next_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:28:24 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/30 12:47:19 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_to_zero(int n, ...)
{
	va_list	numbers;
	int		i;

	i = 0;
	va_start(numbers, n);
	while (i < n)
	{
		*(va_arg(numbers, int *)) = 0;
		i++;
	}
	va_end(numbers);
	return (0);
}

int	is_sep(char c, char sep)
{
	if (c == sep || c == 0)
		return (TRUE);
	return (FALSE);
}

int	count_char(char *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

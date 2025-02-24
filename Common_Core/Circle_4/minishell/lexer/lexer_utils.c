/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:14:28 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/06 09:18:33 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_itoa_copy(char *dest, int n)
{
	int		index;
	int		neg;

	index = ft_nb_len(n);
	neg = 1;
	if (n < 0)
		neg = -1;
	dest[index] = 0;
	index--;
	while (index >= 0)
	{
		if (n < 0)
			dest[index] = -(n % 10) + '0';
		else
			dest[index] = (n % 10) + '0';
		n /= 10;
		index--;
	}
	if (neg < 0)
		dest[0] = '-';
}

int	ft_next_char(char *str, char c)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
	{
		i++;
	}
	if (str[i] == c)
		return (i);
	else
		return (0);
}

/* Checks if the current char modify the quote status. If we are in a quote
sequence, it checks if the current char end that sequence (i.e. if it's the same
quote than the one that began the sequence). If we are not in a quote sequence,
it checks if the current char begin a new sequence (i.e. if it's a quote char
that has a twin further in the string). */
int	check_quotes(char *line, int in_quotes)
{
	if ((in_quotes == '\'' && *line == '\'')
		|| (in_quotes == '\"' && *line == '\"'))
		return (FALSE);
	if (in_quotes == FALSE && *line == '\''
		&& ft_next_char(line, *line))
		return ('\'');
	if (in_quotes == FALSE && *line == '\"'
		&& ft_next_char(line, *line))
		return ('\"');
	return (in_quotes);
}

/* Finds the number of chars that need to be replaced by the env var.
The string will always begin by a '$' and end with the first char that is not
alphanumeric and not a '_' (the only chars authorized in a env var name). */
int	chars_to_replace(char *str)
{
	int	i;

	if (ft_strncmp(str, "$?", 2) == 0 || (str[1] && ft_isdigit(str[1]) == TRUE))
		return (2);
	else if (!str[1] 
		|| (str[1] && ft_isalnum(str[1]) == FALSE && str[1] != '_'))
		return (0);
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) == TRUE || str[i] == '_'))
		i++;
	return (i);
}

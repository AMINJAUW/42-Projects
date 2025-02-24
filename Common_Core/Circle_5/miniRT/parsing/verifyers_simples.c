/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifyers_simples.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:37:43 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 13:43:58 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* These functions return NULL if a string doesn't contain, after skipping its
leading spaces, the properly formatted element searched. If they find such an
element, they will return a pointer to the first char after the element. */

/* Checks if the int we are looking for overflows. Then checks it's a whole
number: an optional '+' or '-', at least one digit, anything else. */
char	*is_whole_number(char *str)
{
	if (int_overflow(str) == TRUE)
		return (NULL);
	while (ft_in_set_char(*str, " \t") == TRUE)
		str++;
	if (*str != '+' && *str != '-' && ft_isdigit(*str) == FALSE)
		return (NULL);
	if (*str == '+' || *str == '-')
		str++;
	if (ft_isdigit(*str) == FALSE)
		return (NULL);
	while (ft_isdigit(*str) == TRUE)
		str++;
	return (str);
}

/* Checks if the float we are looking for overflows. Then looks for a
fractional: an optional '+' or '-', any number of digits, an optional '.'
followed by any number of digits, anything else. */
char	*is_fractional(char *str)
{
	if (isinf(ft_atof(str)) != 0)
		return (NULL);
	while (ft_in_set_char(*str, " \t") == TRUE)
		str++;
	if (*str != '+' && *str != '-' && *str != '.' && ft_isdigit(*str) == FALSE)
		return (NULL);
	if (*str == '+' || *str == '-')
		str++;
	if (*str != '.' && ft_isdigit(*str) == FALSE)
		return (NULL);
	while (ft_isdigit(*str) == TRUE)
		str++;
	if (*str != '.')
		return (str);
	str++;
	while (ft_isdigit(*str) == TRUE)
		str++;
	return (str);
}

/* Looking for a double between min and max included. */
char	*is_fract_range(char *str, double min, double max)
{
	if (ft_atof(str) < min || ft_atof(str) > max)
		return (NULL);
	return (is_fractional(str));
}

/* Looking for a whole number between min and max included. */
char	*is_whole_number_range(char *str, int min, int max)
{
	if (ft_atoi(str) < min || ft_atoi(str) > max)
		return (NULL);
	return (is_whole_number(str));
}

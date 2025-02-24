/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifyers_complex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:33:50 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 13:43:58 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*is_coordinates(char *str)
{
	while (ft_in_set_char(*str, " \t") == TRUE)
		str++;
	str = is_fractional(str);
	if (str == NULL || *str == 0 || *(str++) != ',')
		return (NULL);
	str = is_fractional(str);
	if (str == NULL || *str == 0 || *(str++) != ',')
		return (NULL);
	str = is_fractional(str);
	if (str == NULL)
		return (NULL);
	return (str);
}

char	*is_vector(char *str)
{
	double	x;
	double	y;
	double	z;

	while (ft_in_set_char(*str, " \t") == TRUE)
		str++;
	x = ft_atof(str);
	str = is_fract_range(str, -1, 1);
	if (str == NULL || *str == 0 || *(str++) != ',')
		return (NULL);
	y = ft_atof(str);
	str = is_fract_range(str, -1, 1);
	if (str == NULL || *str == 0 || *(str++) != ',')
		return (NULL);
	z = ft_atof(str);
	str = is_fract_range(str, -1, 1);
	if (str == NULL || (x == 0 && y == 0 && z == 0))
		return (NULL);
	return (str);
}

char	*is_color(char *str)
{
	while (ft_in_set_char(*str, " \t") == TRUE)
		str++;
	str = is_whole_number_range(str, 0, 255);
	if (str == NULL || *str == 0 || *(str++) != ',')
		return (NULL);
	str = is_whole_number_range(str, 0, 255);
	if (str == NULL || *str == 0 || *(str++) != ',')
		return (NULL);
	str = is_whole_number_range(str, 0, 255);
	if (str == NULL)
		return (NULL);
	return (str);
}

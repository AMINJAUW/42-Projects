/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:14:14 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 13:47:26 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_ftoa_add(char buffer[400], double *n, int *index, int *pow_ten)
{
	buffer[*index] = '0' + (*n / pow(10, *pow_ten));
	*n = *n - ((buffer[*index] - '0') * pow(10, *pow_ten));
	(*pow_ten)--;
	(*index)++;
}

/* Uses a buffer of 400 because the biggest integer representable in the form of
a double is not more than 310 characters and we only want 2 digits of precision
after the zero. */
void	ft_ftoa(double n, char buffer[400])
{
	int	index;
	int	pow_ten;

	ft_bzero(buffer, 400);
	index = 0;
	pow_ten = 1;
	if (n < 0)
	{
		buffer[index] = '-';
		n *= -1;
		index++;
	}
	while (pow(10, pow_ten) <= n)
		pow_ten++;
	pow_ten--;
	while (pow_ten > -1)
		ft_ftoa_add(buffer, &n, &index, &pow_ten);
	if (n > 0)
	{
		buffer[index] = '.';
		index++;
	}
	while (n > 0 && pow_ten > -3)
		ft_ftoa_add(buffer, &n, &index, &pow_ten);
}

static void	ft_atof_add(char *str, double *nbr, int *index, int *pow_ten)
{
	*nbr += (str[*index] - '0') * pow(10, *pow_ten);
	(*pow_ten)--;
	(*index)++;
}

/* Returns inf on overflow. */
double	ft_atof(const char *str)
{
	int		index;
	int		sign;
	int		pow_ten;
	double	nbr;

	index = 0;
	sign = 1;
	nbr = 0;
	while (ft_in_set_char(str[index], " \t") == TRUE 
		|| (str[index] >= 9 && str[index] <= 13))
		index++;
	if (str[index] == '-')
		sign *= -1;
	if (str[index] == '+' || str[index] == '-')
		index++;
	while (str[index] >= '0' && str[index] <= '9')
		nbr = (nbr * 10) + (str[index++] - '0');
	if (str[index] == '.')
		index++;
	pow_ten = -1;
	while (str[index] >= '0' && str[index] <= '9')
		ft_atof_add((char *)str, &nbr, &index, &pow_ten);
	return ((double)(nbr * sign));
}

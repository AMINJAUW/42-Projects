/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:12:01 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/25 11:28:14 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	ft_only_zero(char *str)
{
	while (*str)
	{
		if (*str != '0')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int	make_complex(int argc, char **argv, int i, t_info *info)
{
	info->c.re = (float)ft_atoi(argv[i++], TRUE) / 1000;
	if (info->c.re == 0 && !ft_only_zero(argv[i - 1]))
		exit(ft_printf("Please put valid number for Re(c)"));
	if (i < argc)
	{
		if (argv[i][ft_strlen(argv[i]) - 1] == 'i')
			argv[i][ft_strlen(argv[i]) - 1] = 0;
		info->c.im = (float)ft_atoi(argv[i], TRUE) / 1000;
		if (info->c.im == 0 && !ft_only_zero(argv[i]))
			exit(ft_printf("Please put valid number for Im(c) after Re(c)"));
	}
	return (i);
}

void	info_init(t_info *info)
{
	info->c.im = 0.624;
	info->c.re = 0.055;
	info->julia = 0;
	info->mandel = 0;
	info->mlx = 0;
	info->r = 0;
	info->scale = 0.002;
	info->change = 0.01;
	info->sat = 0;
}

void	check_args(int argc, char **argv, t_info *info)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(MANDEL) == ft_strlen(argv[i])
			&& !ft_memcmp(ft_tolower(argv[i]), MANDEL, ft_strlen(MANDEL)))
			info->mandel = 1;
		else if (ft_strlen(JULIA) == ft_strlen(argv[i])
			&&!ft_memcmp(ft_tolower(argv[i]), JULIA, ft_strlen(JULIA)))
			info->julia = 1;
		else if (ft_strlen(argv[i]) == 1
			&& !ft_memcmp(ft_tolower(argv[i]), "r", ft_strlen("r")))
			info->r = 1;
		else if (info->julia)
			i = make_complex(argc, argv, i, info);
		else
			exit(ft_printf("Wrong args, please only use \njulia or mandelbrot\n\
r to reverse the colors\nAnd the Re(c) and Im(c) in thousandths \
in a julia fractal, by default c = 0.055 + 0.624i\n"));
		i++;
	}
	if (!(info->mandel != info->julia))
		exit(ft_printf("You can not have none or both, you must choose\n"));
}

int	main(int argc, char **argv)
{
	t_info	info;

	info_init(&info);
	if (argc == 1)
		return (ft_printf("Wrong args, please only use \njulia or mandelbrot\n\
r to reverse the colors\nAnd the Re(c) and Im(c) in thousandths \
in a julia fractal, by default c = 0.055 + 0.624i\n"));
	check_args(argc, argv, &info);
	init(&info);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:56:15 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 13:55:27 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 3], ".rt", 4) == 0)
		return (TRUE);
	else
		return (FALSE);
}

void	init_scene(t_scene *scene)
{
	errno = 0;
	scene->ambient_lighting = NULL;
	scene->spot_lighting = NULL;
	scene->camera = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
}

int	main(int argc, char **argv)
{
	t_scene	scene;
	t_mlx	mlx;

	(void) argc;
	if (argc != 2 || check_extension(argv[1]) == FALSE)
	{
		printf("miniRT: Usage: ./miniRT file.rt\n");
		exit (0);
	}
	if (X_RES < 800 || Y_RES < 600)
	{
		printf("miniRT: X_RES min = 800, Y_RES min = 600\n");
		exit (0);
	}
	init_scene(&scene);
	file_verify(argv[1]);
	file_parse(argv[1], &scene);
	mlx.scene = &scene;
	init_window(&mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:40:36 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 11:02:16 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	print_error(const char *str)
{
	ft_fprintf(2, "Error\nminiRT: %s", str);
	return (FAIL);
}

void	parsing_error(int fd, char *line, t_scene *scene)
{
	if (errno != 0)
		perror("Error\nminiRT");
	if (fd != -1)
		close(fd);
	if (line != NULL)
		free(line);
	clear_scene(scene);
	exit(1);
}

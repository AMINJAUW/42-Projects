/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:55:37 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/26 11:36:05 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	compute_line(char *line, t_scene *scene)
{
	int	(*create_element)(char*, t_scene*);

	while (ft_in_set_char(*line, " \t") == TRUE)
		line++;
	if (*line == '\n' || *line == '\0')
		return (SUCCES);
	choose_fct(&create_element, line, CREATE);
	return (create_element(line, scene));
}

void	file_parse(char *file, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		parsing_error(-1, NULL, NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL && errno == ENOMEM)
			parsing_error(fd, NULL, scene);
		else if (line == NULL)
			break ;
		if (compute_line(line, scene) == FAIL)
			parsing_error(fd, line, scene);
		free(line);
	}
	close(fd);
}

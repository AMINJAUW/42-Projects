/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:27:07 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/21 13:39:02 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_all(char *str)
{
	free (str);
	return (0);
}

char	*fill_line(int fd, char *line, char *buffer)
{
	int	i;
	int	j;

	i = -1;
	while (buffer[++i] != '\n')
	{
		if (i == BUFFER_SIZE)
		{
			j = read(fd, buffer, BUFFER_SIZE);
			if (j < 0 || (!line[0] && !buffer[0]))
				return (free_all(line));
			if (j == 0)
				return (line);
			i = 0;
		}
		if (buffer[i] == '\n')
			break ;
		if (buffer[i] != 0)
		{
			line = ft_str_cat_char(line, buffer, i);
			if (!line)
				return (0);
		}
	}
	return (ft_str_cat_char(line, buffer, i));
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;

	if (fd < 0)
		return (0);
	line = ft_calloc(1, sizeof(char));
	if (!line)
		return (0);
	line = fill_line(fd, line, buffer);
	if (!line || *line == 0)
		return (0);
	return (line);
}

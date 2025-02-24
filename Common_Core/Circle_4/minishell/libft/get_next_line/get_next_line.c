/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:56:19 by vvalet            #+#    #+#             */
/*   Updated: 2023/09/04 10:10:13 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*append_part(char *line, char *buffer, ssize_t *bytes, int fd)
{
	char	*temp;

	temp = ft_strjoin_gnl(line, buffer);
	ft_bzero_gnl(buffer, BUFFER_SIZE);
	*bytes = read(fd, buffer, BUFFER_SIZE);
	if (*bytes == -1)
	{
		if (line)
			free(line);
		if (temp)
			free(temp);
		ft_bzero_gnl(buffer, BUFFER_SIZE);
		return (NULL);
	}
	if (line)
		free(line);
	return (temp);
}

char	*append_end(char *line, char *buffer, ssize_t bytes)
{
	char	*end;
	char	*temp;

	if (ft_strchr_gnl(buffer, '\n'))
		end = ft_substr_gnl(buffer, 0,
				ft_strchr_gnl(buffer, '\n') - buffer + 1);
	else
		end = ft_substr_gnl(buffer, 0, bytes);
	if (!end)
	{
		free(line);
		return (NULL);
	}
	temp = ft_strjoin_gnl(line, end);
	free(end);
	if (line)
		free(line);
	return (temp);
}

char	*find_line(int fd, char *buffer, ssize_t bytes)
{
	char	*line;

	line = 0;
	while (!ft_strchr_gnl(buffer, '\n'))
	{
		line = append_part(line, buffer, &bytes, fd);
		if (!line)
			return (NULL);
		if (bytes < BUFFER_SIZE)
			break ;
	}
	line = append_end(line, buffer, bytes);
	return (line);
}

void	clean_buffer(char buffer[BUFFER_SIZE + 1])
{
	char	*ptr;
	size_t	index;

	ptr = ft_strchr_gnl(buffer, '\n');
	index = 0;
	while (ptr && ptr[index] && ptr[index + 1])
	{
		buffer[index] = ptr[index + 1];
		index++;
	}
	ft_bzero_gnl(&buffer[index], BUFFER_SIZE - index);
}

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1] = {{0}};
	char		*line;
	ssize_t		bytes;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	bytes = 0;
	if (buffer[fd][0] == 0)
		bytes = read(fd, buffer[fd], BUFFER_SIZE);
	line = find_line(fd, buffer[fd], bytes);
	clean_buffer(buffer[fd]);
	return (line);
}

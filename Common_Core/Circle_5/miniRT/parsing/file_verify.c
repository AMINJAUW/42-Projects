/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_verify.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:55:29 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/26 11:36:15 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* The purpose of array of three ints "objects" is to check that camera (0),
ambient lighting (1) and spot lighting (2) do not appear more than once. */
static int	check_object(char *line, int objects[3])
{
	int			i;
	static char	element[6][3]
		= {"C", "A", "L", "sp", "pl", "cy"};

	i = 0;
	while (i < 6 && ft_strncmp(line, element[i], ft_strlen(element[i])) != 0)
		i++;
	if (i < 3)
		objects[i]++;
	if (i < 3 && objects[i] > 1)
		return (print_error("unique object found twice\n"));
	else if (i < 6)
		return (SUCCES);
	else
		return (print_error("unknown object identifier\n"));
}

static void	verify_line(char *line, int objects[3], int fd)
{
	int	i;
	int	(*verify_element)(char*, t_scene*);

	i = 0;
	while (ft_in_set_char(line[i], " \t") == TRUE)
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return ;
	if (check_object(&line[i], objects) == FAIL)
		parsing_error(fd, line, NULL);
	choose_fct(&verify_element, &line[i], VERIFY);
	if (verify_element(&line[i], NULL) == FAIL)
		parsing_error(fd, line, NULL);
}

/* The purpose of array of three ints "objects" is to check that camera (0),
ambient lighting (1) and spot lighting (2) do not appear more than once. */
void	file_verify(char *file)
{
	int		fd;
	char	*line;
	int		objects[3];

	ft_bzero(objects, sizeof(objects));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		parsing_error(-1, NULL, NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL && errno == ENOMEM)
			parsing_error(fd, NULL, NULL);
		else if (line == NULL)
			break ;
		verify_line(line, objects, fd);
		free(line);
	}
	close(fd);
	if (objects[0] < 1 || objects[1] < 1)
	{
		print_error("required object not found\n");
		parsing_error(-1, NULL, NULL);
	}
}

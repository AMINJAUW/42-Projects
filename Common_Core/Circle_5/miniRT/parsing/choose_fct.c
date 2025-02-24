/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:57:16 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/25 12:32:20 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	choose_fct(int (**fct)(char*, t_scene*), char *line, int type)
{
	int			i;
	static char	element[6][3]
		= {"C", "A", "L", "sp", "pl", "cy"};
	static int	(*verify_fct[6])(char*, t_scene*)
		= {verify_cam, verify_al, verify_sl, verify_sphere, verify_plane,
		verify_cylinder};
	static int	(*create_fct[6])(char*, t_scene*)
		= {create_cam, create_al, create_sl, create_sphere, create_plane,
		create_cylinder};

	i = 0;
	while (i < 6 && ft_strncmp(line, element[i], ft_strlen(element[i])) != 0)
		i++;
	if (i < 6 && type == VERIFY)
		*fct = verify_fct[i];
	else if (i < 6 && type == CREATE)
		*fct = create_fct[i];
	else
		*fct = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_artolist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:47:37 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/02 14:13:16 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_artolist(char **ar)
{
	t_list	*list;
	t_list	*instance;

	list = ft_lstnew(*ar);
	ar++;
	while (*ar)
	{
		instance = ft_lstnew(*ar);
		if (instance == NULL)
		{
			ft_lstclear(&list, &free);
			return (NULL);
		}
		ft_lstadd_back(&list, instance);
		ar++;
	}
	return (list);
}

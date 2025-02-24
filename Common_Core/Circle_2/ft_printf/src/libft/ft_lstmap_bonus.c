/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:00:06 by aminjauw          #+#    #+#             */
/*   Updated: 2023/04/09 11:26:19 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*delete_all(t_list *start, void (*del)(void *), void *content)
{
	t_list	*temp;
	t_list	*temp2;

	if (start)
	{
		temp = start->next;
		ft_lstdelone(start, del);
		while (temp)
		{
			temp2 = temp;
			temp = temp->next;
			ft_lstdelone(temp2, del);
		}
	}
	(*del)(content);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	void	*f_content;

	if (!lst || !f)
		return (0);
	f_content = (*f)(lst->content);
	new = ft_lstnew(f_content);
	if (!new)
		return (delete_all(new, del, f_content));
	temp = new;
	lst = lst->next;
	while (lst != 0)
	{
		f_content = (*f)(lst->content);
		temp->next = ft_lstnew(f_content);
		if (!(temp->next))
			return (delete_all(new, del, f_content));
		temp = temp->next;
		lst = lst->next;
	}
	return (new);
}

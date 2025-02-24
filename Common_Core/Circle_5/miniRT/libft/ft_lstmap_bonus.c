/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:10:49 by vvalet            #+#    #+#             */
/*   Updated: 2023/07/14 16:09:25 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_clear(t_list *lst, void *cont, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*next;

	del(cont);
	ptr = lst;
	while (ptr)
	{
		next = ptr->next;
		del(ptr->content);
		free(ptr);
		ptr = next;
	}
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*new_cont;
	t_list	*new_list;
	t_list	*new_el;

	if (!lst || !f || !del)
		return (NULL);
	new_cont = f(lst->content);
	new_list = ft_lstnew(new_cont);
	if (!new_list)
		return (ft_clear(new_list, new_cont, del));
	lst = lst->next;
	while (lst)
	{
		new_cont = f(lst->content);
		new_el = ft_lstnew(new_cont);
		if (!new_el)
			return (ft_clear(new_list, new_cont, del));
		ft_lstadd_back(&new_list, new_el);
		lst = lst->next;
	}
	return (new_list);
}

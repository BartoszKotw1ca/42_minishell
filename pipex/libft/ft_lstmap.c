/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:08:08 by jponieck          #+#    #+#             */
/*   Updated: 2024/01/22 19:08:12 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	clear_list(t_list **lst, void (*del)(void *))
{
	t_list	*list;
	t_list	*empty;

	list = *lst;
	while (list != NULL || list->next != NULL)
	{
		(*del)(list->content);
		empty = list;
		list = list->next;
		free(empty);
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlist;
	t_list	*nlist_next;

	if (!lst)
		return (NULL);
	nlist = ft_lstnew((*f)(lst->content));
	if (!nlist)
		return (NULL);
	lst = lst->next;
	while (lst != NULL)
	{
		nlist_next = ft_lstnew((*f)(lst->content));
		if (!nlist_next)
		{
			clear_list(&nlist, del);
			return (NULL);
		}
		ft_lstadd_back(&nlist, nlist_next);
		lst = lst->next;
	}
	return (nlist);
}

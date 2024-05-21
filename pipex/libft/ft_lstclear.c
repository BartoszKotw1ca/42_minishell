/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:52:58 by jponieck          #+#    #+#             */
/*   Updated: 2024/03/12 10:53:03 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;
	t_list	*current;

	list = *lst;
	if (list && del)
	{
		while (list->next != NULL)
		{
			if (list->content)
				(*del)(list->content);
			current = list;
			list = list->next;
			free(current);
		}
		if (list->content)
			(*del)(list->content);
		free(list);
	}
	*lst = NULL;
}

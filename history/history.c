/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:26:21 by bkotwica          #+#    #+#             */
/*   Updated: 2024/05/28 13:56:48 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_add_history(t_list **lista, char *str)
{
	ft_lstadd_back(lista, ft_lstnew(str));
}

void	print_history(t_list *lista)
{
	int	i;

	i = 1;
	while (lista)
	{
		printf("%d  %s\n", i, (char *)lista->content);
		lista = lista->next;
		i ++;
	}
}

void	del_node(void *content)
{
	free(content);
}

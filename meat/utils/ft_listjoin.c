/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:33:45 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/07 15:16:56 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//that file contains the functions that join the list of strings into one string
// for example ["ls", "-l", "-a"] -> "ls -l -a"
size_t	char_in_list(int start, int end, char **lista, int i)
{
	size_t	len;

	len = 0;
	while (lista[start] && start <= end)
	{
		i = 0;
		while (lista[start][i])
			i ++;
		len += i + 1;
		start ++;
	}
	return (len);
}

char	*ft_listjoin(int start, int end, char **lista)
{
	char	*joined;
	size_t	i;
	size_t	len;

	i = 0;
	len = char_in_list(start, end, lista, 0);
	joined = malloc(sizeof(char) * (len + 1));
	if (!joined)
		return (NULL);
	if (!joined)
		return (NULL);
	len = 0;
	while (lista[start] && start <= end)
	{
		i = 0;
		while (lista[start][i])
			joined[len ++] = lista[start][i ++];
		joined[len ++] = ' ';
		start ++;
	}
	joined[len] = '\0';
	return (joined);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_tabs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:06:23 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/24 09:21:30 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_skip_tabs(char *line)
{
	int		i;
	int		len;
	char	*li;

	len = 0;
	i = -1;
	while (line[++ i])
	{
		if (line[i] == '	')
			continue ;
		len ++;
	}
	li = malloc(sizeof(char) * (len + 1));
	li[len] = '\0';
	i = -1;
	len = 0;
	while (line[++ i])
	{
		if (line[i] == '	')
			continue ;
		li[len ++] =  line[i];
	}
	free(line);
	return (li);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_everyone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:20:37 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/20 10:21:51 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*create_outfile(char **tmp, int i, int j, int tm)
{
	char	*temp;

	temp = malloc(sizeof(char) * (tm - j + 1));
	temp[tm - j] = '\0';
	tm = 0;
	while (tmp[i][j])
		temp[tm++] = tmp[i][j ++];
	tmp[i][ft_strlen(tmp[i]) - ft_strlen(temp)] = '\0';
	return (temp);
}

void	close_pipes(t_process *p, int i)
{
	close(p->pipes[i - 1][0]);
	close(p->pipes[i - 1][1]);
}

void	free_memories(void *mem1, void *mem2)
{
	free(mem1);
	if (((char *)mem2)[0] == -2)
		free(mem2);
}

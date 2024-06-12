/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipex_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:02:41 by jponieck          #+#    #+#             */
/*   Updated: 2024/06/12 22:51:05 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	rewrite_commands(t_data *d, int i, int j)
{
	t_com	*rewr;
	t_com	*rewr_start;

	while(i < d->num_of_com)
	{
		if (d->com[i].infile && i != 0)
			j ++;
		i ++;
	}
	rewr = malloc(sizeof(t_com) * (d->num_of_com + j));
	rewr_start = rewr;
	i = 0;
	while (i < d->num_of_com)
	{

		rewr->commend = ft_strdup(d->com[i].commend);
		if (d->com[i].infile)
			rewr->infile = ft_strdup(d->com[i].infile);
		if (d->com[i].outfile)
			rewr->outfile = ft_strdup(d->com[i].outfile);
		rewr->mode = d->com[i].mode;
		if (i > 0 && d->com[i].infile)
		{
			rewr ++;
			rewr->commend = ft_strdup("cat");
			rewr->infile = NULL;
			rewr->outfile = NULL;
			rewr->mode = 0;
		}
		i++;
		rewr++;
	}
	d->com = rewr_start;
	d->num_of_com += j;
}

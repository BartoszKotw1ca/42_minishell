/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipex_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:02:41 by jponieck          #+#    #+#             */
/*   Updated: 2024/06/19 11:03:34 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_path(t_main_struct *main_data)
{
	char	*path;
	char	key[5] = {'P', 'A', 'T', 'H', '\0'};

	// key = {'P', 'A', 'T', 'H', '\0'};
	path = read_env(main_data, key);
	if (path)
		return ft_split(path, ':');
	else
		return (ft_split("", ':'));
}

static void	replace_cat(t_data *d, int i)
{
	free(d->com[i].commend);
	d->com[i].commend = ft_strdup("true ");
}

void	rewrite_commands(t_data *d, int i, int j)
{
	char	*cat_friendly;

	cat_friendly = "grep,awk,sed,cut,sort,uniq,head,tail,wc,tr,tee,xargs";
	while(i < d->num_of_com)
	{
		if (strncmp(d->com[i].commend, "cat ", ft_strlen(d->com[i].commend)) == 0 && i + 1 != d->num_of_com)
		{
			while (d->com[i + 1].commend[j] && d->com[i + 1].commend[j] != ' ')
				j++;
			d->com[i + 1].commend[j] = 0;
			if (!ft_strnstr(cat_friendly, d->com[i + 1].commend, ft_strlen(cat_friendly)))
				replace_cat(d, i);
			else
				d->com[i + 1].commend[j] = ' ';
		}
		i ++;
	}
}

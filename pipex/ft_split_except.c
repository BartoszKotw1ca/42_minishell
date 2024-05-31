/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_except.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:44:36 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/31 22:17:13 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*prepare_string(t_split_data *sd, int i)
{
	while (*sd->src)
	{
		if (*sd->src == sd->in_ef)
		{
			sd->in_ef = 0;
			sd->src++;
			continue;
		}
		if ((*sd->src == sd->e || *sd->src == sd->f) && sd->in_ef == 0)
		{
			sd->in_ef = *sd->src;
			sd->src++;
			continue ;
		}
		if (*sd->src == sd->c && sd->in_ef != 0)
			sd->new[i] = -5;
		else
			sd->new[i] = *sd->src;
		sd->src++;
		i++;
	}
}

void	**back_to_original(char **splited, int i, int j)
{
	while(splited[i])
	{
		while(splited[i][j])
		{
			if (splited[i][j] == -5)
				splited[i][j] = ' ';
			j++;
		}
		j = 0;
		i++;
	}
}

char	**ft_split_except(char *src, char c, char e, char f)
{
	char			*src_new;
	char			**splited;
	t_split_data	sd;

	sd.src = src;
	sd.new = ft_calloc(ft_strlen(src) + 1, sizeof(char));
	sd.c = c;
	sd.e = e;
	sd.f = f;
	sd.in_ef = 0;
	prepare_string(&sd, 0);
	splited = ft_split(sd.new, c);
	back_to_original(splited, 0, 0);
	free(sd.new);
	return (splited);
}

// int main(int ac, char **av)
// {
// 	char	**result;

// 	result = ft_split_except(av[1], ' ', 39);
// 	int i = 0;
// 	while (result[i])
// 	{
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);
// }

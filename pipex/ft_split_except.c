/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_except.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:44:36 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/30 14:39:49 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prepare_string(char *src, char c, char e)
{
	char	*new;
	int		i;
	int		in_e;

	i = 0;
	in_e = -1;
	new = ft_calloc(ft_strlen(src) + 1, sizeof(char));
	while (*src)
	{
		if (*src == e)
		{
			in_e *= -1;
			src++;
			continue ;
		}
		if (*src == c && in_e == 1)
			new[i] = -5;
		else
			new[i] = *src;
		src++;
		i++;
	}
	return (new);
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

char	**ft_split_except(char *src, char c, char e)
{
	char	*src_new;
	char	**splited;

	src_new = prepare_string(src, c, e);
	splited = ft_split(src_new, c);
	back_to_original(splited, 0, 0);
	free(src_new);
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

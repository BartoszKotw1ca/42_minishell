/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:15:53 by jponieck          #+#    #+#             */
/*   Updated: 2024/06/16 15:12:38 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_paths(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 5))
			data->paths = ft_split(envp[i], ':');
		i++;
	}
}

void	free_split(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		if (res[i])
			free(res[i]);
		i++;
	}
	if (res)
		free(res);
}

void	print_error(char *mes1, char *mes2)
{
	write(2, "\033[31m", 6);
	write(2, mes1, ft_strlen(mes1));
	write(2, ": ", 3);
	write(2, mes2, ft_strlen(mes2));
	write(2, "\033[0m", 5);
}

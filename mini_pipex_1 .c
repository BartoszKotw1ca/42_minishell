/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipex .c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:00:18 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/25 19:09:23 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_split(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}

static char	*find_path(char *command, t_data *data)
{
	int		i;
	char	*curr_path;
	char	*prog_path;

	if (!command)
		return (NULL);
	prog_path = ft_strjoin("/", command);
	if (!prog_path)
		return (NULL);
	i = 0;
	while (data->paths[i])
	{
		curr_path = ft_strjoin(data->paths[i], prog_path);
		if (!curr_path)
			return (NULL);
		if (access(curr_path, F_OK) == 0)
		{
			free(prog_path);
			return (curr_path);
		}
		free(curr_path);
		i++;
	}
	free(prog_path);
	return ("no_prog");
}

void	mini_pipex(t_data *data)
{
	t_process	p;
	int			*pids;
	int			(*pipes)[2];
	int			i;

	pipes = malloc(data->num_of_com * sizeof(int[2]));
	pids = malloc(data->num_of_com * sizeof(int) + 1);
	i = 0;
	while (i < data->num_of_com)
		pipe(pipes[i++]);
	i = 0;
	while (i < data->num_of_com)
	{
		printf("%d, %d\n", pipes[i][0], pipes[i][1]);
		i++;
	}
	free (pipes);
	free (pids);
	return;
}

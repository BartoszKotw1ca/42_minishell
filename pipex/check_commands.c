/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:30:53 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/28 14:24:52 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char *command, t_data *data)
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
	return (ft_strjoin("", "no_prog"));
}

void	check_commands(t_process *p, t_data *data)
{
	int	i;

	i = 0;
	if (ft_strncmp("no_prog", p->path, 7) == 0)
	{
		print_error(p->args[0], "command not found\n");
		free_split(p->args);
		free(p->path);
		p->args = ft_split("echo -n", ' ');
		p->path = find_path("echo", data);
	}
}
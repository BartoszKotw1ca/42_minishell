/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:30:53 by jponieck          #+#    #+#             */
/*   Updated: 2024/06/07 15:17:17 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*check_absolute(char *command)
{
	if (access(command, F_OK) == 0)
		return (ft_strjoin("", command));
	return (ft_strjoin("", "no_prog"));
}

char	*find_path(char *command, t_data *data, int i)
{
	char	*curr_path;
	char	*prog_path;

	if (!command)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (check_absolute(command));
	prog_path = ft_strjoin("/", command);
	if (!prog_path)
		return (NULL);
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

void	check_files(t_process *p, t_data *data)
{
	if (data->infile && data->infile_ok != 0)
	{
		free(p->args[0]);
		p->args[0] = ft_strjoin("true", "");
		free(p->path);
		p->path = ft_strjoin("/usr/bin/", "true");
	}
}

void	check_commands(t_process *p, t_data *data)
{
	int		i;

	i = 0;
	if (ft_strncmp("cd", p->args[0], 2) == 0)
	{
		while (p->args[i])
			i++;
		if (i > 2)
			print_error(p->args[0], "to many arguments\n");
		else if (chdir(p->args[1]) != 0)
			print_error(p->args[1], "no such directory\n");
		free(p->path);
		p->path = ft_strjoin("/usr/bin/", "true");
		free(p->args[0]);
		p->args[0] = ft_strjoin("true", "");
		return ;
	}
	i = 0;
	if (ft_strncmp("no_prog", p->path, 7) == 0)
	{
		print_error(p->args[0], "command not found\n");
		free(p->path);
		p->path = ft_strjoin("/usr/bin/", p->args[0]);
	}
	check_files(p, data);
}

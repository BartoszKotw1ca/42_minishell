/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:30:53 by jponieck          #+#    #+#             */
/*   Updated: 2024/06/24 10:27:32 by bkotwica         ###   ########.fr       */
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

int	check_commands_sec(int i, t_process *p)
{
	if (!(p->args[0]))
		return (0);
	if (ft_strncmp("cd", p->args[0], 2) == 0)
	{
		while (p->args[i])
			i++;
		if (i != 2)
			print_error(p->args[0], "invalid number of arguments\n");
		else if (chdir(p->args[1]) != 0)
			print_error(p->args[1], "no such directory\n");
		free(p->path);
		p->path = ft_strjoin("/usr/bin/", "true");
		free(p->args[0]);
		p->args[0] = ft_strjoin("true", "");
		return (0);
	}
	return (1);
}

void	check_commands(t_process *p, t_data *data, t_main_struct *main_data)
{
	if (check_commands_sec(0, p) == 0)
		return ;
	if (ft_strncmp("env", p->args[0], 3) == 0)
	{
		free(p->path);
		p->path = ft_strjoin("/usr/bin/", "echo");
		free(p->args[0]);
		free(p->args);
		p->args = malloc(4 * sizeof(char *));
		p->args[0] = ft_strjoin("echo", "");
		p->args[1] = ft_strjoin("-n", "");
		p->args[2] = get_env_string(main_data);
		p->args[3] = NULL;
		return ;
	}
	if (ft_strncmp("no_prog", p->path, 7) == 0)
	{
		print_error(p->args[0], "command not found\n");
		free(p->path);
		p->path = ft_strjoin("/usr/", p->args[0]);
	}
	check_files(p, data);
}

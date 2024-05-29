/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:00:18 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/29 19:19:15 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_n_dup(int i, int (*fd)[2], int noc, t_data *data)
{
	int	ifd;
	int	ofd;

	if (i == -1 && data->infile)
	{
		ifd = open(data->infile, O_RDONLY);
		dup2(ifd, 0);
		close(ifd);
	}
	if (i + 2 != noc)
		dup2(fd[i + 1][1], 1);
	else if (data->outfile)
	{
		ofd = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dup2(ofd, 1);
		close(ofd);
	}
	if (i > -1)
	{
		close(fd[i][1]);
		dup2(fd[i][0], 0);
		close(fd[i][0]);
	}
}

static void	close_pipes(t_process *p, int i)
{
	close(p->pipes[i - 1][0]);
	close(p->pipes[i - 1][1]);
}

static void	run_commands(t_data *data, t_process *p, int i)
{
	while (i < data->num_of_com)
	{
		p->args = ft_split(data->commends[i], ' ');
		p->path = find_path(p->args[0], data);
		p->pid[i] = fork();
		if (p->pid[i] == 0)
		{
			check_commands(p, data);
			close_n_dup(i - 1, p->pipes, data->num_of_com, data);
			if (i != 0)
				waitpid(p->pid[i - 1], NULL, 0);
			if (execve(p->path, p->args, NULL) != 0)
				perror("");
			return ;
		}
		if (i > 0)
			close_pipes(p, i);
		free_split(p->args);
		free(p->path);
		i++;
	}
	waitpid(p->pid[i - 1], NULL, 0);
}

void	mini_pipex(t_data *data)
{
	t_process	p;
	int			i;
	int			main_pid;

	p.pipes = malloc((data->num_of_com - 1) * sizeof(int[2]));
	p.pid = malloc(data->num_of_com * sizeof(int));
	while (i < data->num_of_com - 1)
		pipe(p.pipes[i++]);
	run_commands(data, &p, 0);
	free (p.pipes);
	free (p.pid);
}

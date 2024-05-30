/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:00:18 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/30 20:51:59 by jponieck         ###   ########.fr       */
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

static char	*read_var_name(char *src)
{
	char	*end;
	char	*var_name;
	int		i;

	i = 0;
	end = ft_strchr(src, ' ');
	if (!end)
		end = src + ft_strlen(src);
	var_name = calloc(end - src + 1, sizeof(char));
	while (&src[i] != end)
	{
		var_name[i] = src[i];
		i++;
	}
	return (var_name);
}

static void	update_arg(t_data *d, int i, char *var_value)
{
	char	*dollar;
	char	*var_end;
	char	*temp1;
	char	*temp2;

	dollar = ft_strchr(d->commends[i], '$');
	var_end = ft_strchr(dollar, ' ');
	if (!var_end)
		var_end = dollar + ft_strlen(dollar);
	*dollar = 0;
	temp1 = ft_strjoin(d->commends[i], var_value);
	temp2 = ft_strjoin(temp1, var_end);
	free(d->commends[i]);
	d->commends[i] = temp2;
	free(temp1);
}

static void	check_args(t_data *d, int i, int j)
{
	char	*var_name;
	char	*var_value;
	int		in_sngl;

	in_sngl = -1;
	while (d->commends[i][j])
	{
		if (d->commends[i][j] == 39)
			in_sngl *= -1;
		if (d->commends[i][j] == '$' && in_sngl == -1)
		{
			var_name = read_var_name(&d->commends[i][j] + 1);
			var_value = getenv(var_name);
			if (var_value)
				update_arg(d, i, var_value);
			free(var_name);
		}
		j++;
	}
}

static void	run_commands(t_data *data, t_process *p, int i)
{
	while (i < data->num_of_com)
	{
		check_args(data, i, 0);
		p->args = ft_split_except(data->commends[i], ' ', 39, 34);
		p->path = find_path(p->args[0], data, 0);
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

	i = 0;
	p.pipes = malloc((data->num_of_com - 1) * sizeof(int[2]));
	p.pid = malloc(data->num_of_com * sizeof(int));
	while (i < data->num_of_com - 1)
		pipe(p.pipes[i++]);
	run_commands(data, &p, 0);
	free (p.pipes);
	free (p.pid);
}

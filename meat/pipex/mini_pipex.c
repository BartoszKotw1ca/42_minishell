/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:00:18 by jponieck          #+#    #+#             */
/*   Updated: 2024/06/09 23:11:37 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	update_arg(t_data *d, int i, char *var_value, int j)
{
	char	*dollar;
	char	*var_end;
	char	*temp1;
	char	*temp2;

	dollar = ft_strchr(d->commends[i], '$');
	var_end = NULL;
	if (dollar[j] == '?')
		var_end = &dollar[j + 1];
	else
	{
		while (ft_isalnum(dollar[j]) != 0 || dollar[j] == '_')
			j++;
		var_end = &dollar[j];
	}
	*dollar = 0;
	if (!var_value)
		var_value = "";
	temp1 = ft_strjoin(d->commends[i], var_value);
	temp2 = ft_strjoin(temp1, var_end);
	free(d->commends[i]);
	d->commends[i] = temp2;
	free(temp1);
}

static void	check_args(t_data *d, int i, int j, t_main_struct *main_data)
{
	char	*var_name;
	char	*var_value;
	int		in_quotes;

	in_quotes = 0;
	while (d->commends[i][j])
	{
		if ((d->commends[i][j] == 39
			|| d->commends[i][j] == 34) && in_quotes == 0)
			in_quotes = d->commends[i][j];
		else if (d->commends[i][j] == in_quotes)
			in_quotes = 0;
		if (d->commends[i][j] == '$' && in_quotes != 39)
		{
			var_name = read_var_name(&d->commends[i][j] + 1);
			if (var_name[0] == '?')
				var_value = read_file("TMP_TODO/status.txt");
			else
				var_value = read_env(main_data, var_name);
			update_arg(d, i, var_value, 1);
			free(var_name);
		}
		j++;
	}
}

static void	run_commands(t_data *data, t_process *p,
	int i, t_main_struct *main_data)
{
	while (i < data->num_of_com)
	{
		check_args(data, i, 0, main_data);
		p->args = ft_split_except(data->commends[i], ' ', 39, 34);
		p->path = find_path(p->args[0], data, 0);
		check_commands(p, data, main_data);
		p->pid[i] = fork();
		if (p->pid[i] == 0)
		{
			// check_commands(p, data, main_data);
			close_n_dup(i - 1, p->pipes, data->num_of_com, data);
			if (i != 0)
				waitpid(p->pid[i - 1], &data->ex_stat, 0);
			execve(p->path, p->args, NULL);
			free_dataa(data, data->tmp);
			exit (errno);
		}
		if (i > 0)
			close_pipes(p, i);
		free_split(p->args);
		free(p->path);
		i++;
	}
	waitpid(p->pid[i - 1], &data->ex_stat, 0);
	update_file("TMP_TODO/status.txt", data->ex_stat);
}

void	mini_pipex(t_data *data, t_main_struct *main_data)
{
	t_process	p;
	int			i;
	int			main_pid;

	i = 0;
	p.pipes = malloc((data->num_of_com - 1) * 8);
	p.pid = malloc(data->num_of_com * sizeof(int));
	while (i < data->num_of_com - 1)
		pipe(p.pipes[i++]);
	run_commands(data, &p, 0, main_data);
	free (p.pipes);
	free (p.pid);
}

//	p.pipes = malloc((data->num_of_com - 1) * sizeof(int[2]));

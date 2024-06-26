/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:00:18 by jponieck          #+#    #+#             */
/*   Updated: 2024/06/24 14:26:41 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	update_arg(t_data *d, int i, char *var_value, int j)
{
	char	*dollar;
	char	*var_end;
	char	*temp1;
	char	*temp2;

	if (var_value[0] == -2)
		var_value++;
	dollar = ft_strchr(d->com[i].commend, '$');
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
	temp1 = ft_strjoin(d->com[i].commend, var_value);
	temp2 = ft_strjoin(temp1, var_end);
	free(d->com[i].commend);
	d->com[i].commend = temp2;
	free_memories(temp1, var_value - 1);
}

static void	check_args(t_data *d, int i, int j, t_main_struct *main_data)
{
	char	*var_name;
	char	*var_value;
	int		in_quotes;

	in_quotes = 0;
	while (d->com[i].commend[++ j])
	{
		if ((d->com[i].commend[j] == 39
				|| d->com[i].commend[j] == 34) && in_quotes == 0)
			in_quotes = d->com[i].commend[j];
		else if (d->com[i].commend[j] == in_quotes)
			in_quotes = 0;
		if (d->com[i].commend[j] == '$' && in_quotes != 39)
		{
			var_name = read_var_name(&d->com[i].commend[j] + 1);
			if (var_name[0] == '?')
				var_value = read_file("/TMP_TODO/status.txt", main_data);
			else
				var_value = read_env(main_data, var_name);
			if (!var_value)
				var_value = ft_strdup("");
			update_arg(d, i, var_value, 1);
			free(var_name);
		}
	}
}

void	free_exec(t_data *data, t_main_struct *main_data, t_process *p)
{
	ft_lstclear(&main_data->history, del_node);
	ft_lstclear(&main_data->envr, del_node);
	rl_clear_history();
	free_after_mixed(data, data, main_data->line);
	free_dataa(data, data->tmp);
	free (p->pipes);
	free (p->pid);
	free(main_data->lines);
	execve(p->path, p->args, NULL);
	free_split(p->args);
	free(p->path);
	free(main_data->line);
	exit (errno);
}

static void	run_commands(t_data *data, t_process *p,
	int i, t_main_struct *main_data)
{
	while (i < data->num_of_com)
	{
		check_args(data, i, -1, main_data);
		p->args = ft_split_except(data->com[i].commend, ' ', 39, 34);
		p->path = find_path(p->args[0], data, 0);
		check_commands(p, data, main_data);
		main_data->sa.sa_handler = do_nothing;
		sigaction(SIGINT, &main_data->sa, NULL);
		p->pid[i] = fork();
		if (p->pid[i] == 0)
		{
			handle_input(i, p->pipes, data);
			handle_output(i, p->pipes, data->num_of_com, data);
			free_exec(data, main_data, p);
		}
		if (i > 0)
			close_pipes(p, i);
		free_split(p->args);
		free(p->path);
		i++;
	}
	waitpid(p->pid[i - 1], &data->ex_stat, 0);
	main_data->sa.sa_handler = ctr_c_sig_handler;
	sigaction(SIGINT, &main_data->sa, NULL);
	update_file("/TMP_TODO/status.txt", data->ex_stat, main_data);
}

void	mini_pipex(t_data *data, t_main_struct *main_data)
{
	t_process	p;
	int			i;

	i = 0;
	rewrite_commands(data, 0, 0);
	p.pipes = malloc((data->num_of_com - 1) * 8);
	p.pid = malloc(data->num_of_com * sizeof(int));
	while (i < data->num_of_com - 1)
	{
		pipe(p.pipes[i]);
		i++;
	}
	run_commands(data, &p, 0, main_data);
	free (p.pipes);
	free (p.pid);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:44:28 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/24 09:24:00 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_to_main_struct(int ac, char **av, char **envp,
	t_main_struct *main_data)
{
	(void) ac;
	(void) av;
	main_data->envp = envp;
	set_env(main_data, main_data->envp);
	main_data->history = NULL;
	main_data->path = getenv("PATH");
}

int	split_main_job(t_main_struct *main_data)
{
	if (check_quotes(main_data->line) == 1)
		printf("Invalid argument!\n");
	else if (ft_strncmp(main_data->line, "exit", 4) == 0)
	{
		free(main_data->line);
		return (1);
	}
	else if (ft_strncmp(main_data->line, "history", 7) == 0)
		print_history(main_data->history);
	else if (ft_strncmp(main_data->line, "cd", 2) == 0)
		change_directory(main_data->line, main_data);
	else if (ft_strncmp(main_data->line, "export", 6) == 0)
		initialize_export(main_data);
	else if (ft_strncmp(main_data->line, "unset", 5) == 0)
		initialize_unset(main_data);
	else
		split_jobs(main_data->line, main_data);
	return (0);
}

char	**break_readline(char *src, int i, t_main_struct *main_data)
{
	char	**lines;
	char	*new_line;

	if (!src)
		return (NULL);
	src = ft_skip_tabs(src);
	src = add_line_to_history(src, main_data);
	prepare_source(src, 0, 0);
	lines = ft_split(src, -5);
	free(src);
	while (lines[++ i])
	{
		if (i != 0)
		{
			new_line = ft_calloc(sizeof(char), ft_strlen(lines[i]) + 3);
			new_line[0] = '<';
			ft_strlcpy(&new_line[1], lines[i], ft_strlen(lines[i]) + 3);
			free(lines[i]);
			if (new_line[1] == -6)
				new_line[1] = '<';
			lines[i] = new_line;
			finish_first_part(lines, i - 1, 0);
		}
	}
	return (lines);
}

void	run_main_program(t_main_struct *main_data, int i, int c)
{
	while (1)
	{
		i = 0;
		main_data->lines = break_readline(readline("$> "), -1, main_data);
		if (!main_data->lines)
			return ;
		while (main_data->lines[i])
		{
			main_data->tmp = main_data->lines[i];
			c = check_line(main_data);
			if (c == 1)
				return ;
			if (split_main_job(main_data) == 1)
				return ;
			if (main_data->line)
				free(main_data->line);
			main_data->line = NULL;
			rl_on_new_line();
			i++;
		}
		free(main_data->lines);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_main_struct	main_data;

	main_data.lines = NULL;
	if (!envp[0])
		return (printf("There is no env, little shit!"), 1);
	signal_prepare(&main_data);
	write_to_main_struct(ac, av, envp, &main_data);
	getcwd(main_data.main_path, 200);
	update_file("/TMP_TODO/status.txt", 0, &main_data);
	run_main_program(&main_data, 0, 0);
	ft_lstclear(&main_data.history, del_node);
	ft_lstclear(&main_data.envr, del_node);
	rl_clear_history();
	free(main_data.lines);
	return (0);
}
// unlink("term"); it was just before return 0;

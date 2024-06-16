/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:44:28 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/16 18:59:54 by jponieck         ###   ########.fr       */
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

int	check_quotes(char *argv)
{
	int		i;
	int		doubl;
	int		one;

	i = -1;
	doubl = 0;
	one = 0;
	while (argv[++ i])
	{
		if (argv[i] == 39 && one == 0)
			one = 1;
		else if (argv[i] == 34 && doubl == 0)
			doubl = 1;
		else if (argv[i] == 39 && one == 1)
			one = 0;
		else if (argv[i] == 34 && doubl == 1)
			doubl = 0;
	}
	if (doubl == 0 && one == 0)
		return (0);
	return (1);
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
		change_directory(main_data->line, main_data->path, main_data);
	// else if (ft_strncmp(main_data->line, "env", 3) == 0)
	// 	print_env(main_data);
	else if (ft_strncmp(main_data->line, "export", 6) == 0)
		initialize_export(main_data);
	else if (ft_strncmp(main_data->line, "unset", 5) == 0)
		initialize_unset(main_data);
	else
		split_jobs(main_data->line, main_data->path, main_data);
	return (0);
}

int	check_line(t_main_struct *main_data)
{
	// if (main_data->tmp == NULL)
	// {
	// 	free(main_data->tmp);
	// 	return (1);
	// }
	main_data->line = ft_strtrim(main_data->tmp, " ");
	free(main_data->tmp);
	// if ((int)main_data->line[0] != 0
	// 	&& same(main_data->history, main_data->line) == 0)
	// {
	// 	my_add_history(&main_data->history, ft_strdup(main_data->line));
	// 	add_history(main_data->line);
	// }
	return (0);
}

char	*add_line_to_history(char *src, t_main_struct *main_data)
{
	char	*line;

	line = ft_strtrim(src, " ");
	free(src);
	if ((int)line[0] != 0 && same(main_data->history, line) == 0)
	{
		my_add_history(&main_data->history, ft_strdup(line));
		add_history(line);
	}
	return (line);
}

void	prepare_source(char *src, int i, int init)
{
	while (src[i])
	{
		if (src[i] == '|')
			init = 1;
		if (init == 1 && src[i] == '<')
		{
			src[i] = -5;
			if (src[i + 1] == '<')
				src[i + 1] = -6;
		}
		if (src[i] != ' ' && src[i] != '<' && src[i] != '|')
			init = 0;
		i++;
	}
}

void	finish_first_part(char **lines, int i, int j)
{
	char	*new_line;

	new_line = ft_calloc(sizeof(char), ft_strlen(lines[i]) + 7);
	while (lines[i][j] != '|')
		j++ ;
	ft_memcpy(new_line, lines[i], ft_strlen(lines[i]));
	ft_memcpy(&new_line[j] + 1, " true", 5);
	free(lines[i]);
	lines[i] = new_line;
}

char	**break_readline(char *src, int i, t_main_struct *main_data)
{
	char	**lines;
	char	*new_line;

	if (!src)
		return (NULL);
	src = add_line_to_history(src, main_data);
	prepare_source(src, 0, 0);
	lines = ft_split(src, -5);
	free(src);
	while (lines[i])
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
		i++;
	}
	return (lines);
}

int	main(int ac, char **av, char **envp)
{
	t_main_struct	main_data;
	int				c;
	int				i;
	char			**lines;

	if (!envp[0])
		return (printf("There is no env, little shit!"), 1);
	signal_prepare(&main_data);
	write_to_main_struct(ac, av, envp, &main_data);
	while (1)
	{
		i = 0;
		lines = break_readline(readline("$> "), 0, &main_data);
		while (lines[i])
		{
			main_data.tmp = lines[i];
			c = check_line(&main_data);
			if (c == 1)
				break ;
			if (split_main_job(&main_data) == 1)
			{
				c = 1;
				break ;
			}
			if (main_data.line)
				free(main_data.line);
			main_data.line = NULL;
			rl_on_new_line();
			set_context_string(main_data.line);
			i++;
		}
		free(lines);
		if (c == 1)
			break;
	}
	ft_lstclear(&main_data.history, del_node);
	ft_lstclear(&main_data.envr, del_node);
	rl_clear_history();
	return (0);
}
// unlink("term"); it was just before return 0;

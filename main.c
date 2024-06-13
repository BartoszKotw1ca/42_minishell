/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:44:28 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/12 18:51:51 by bkotwica         ###   ########.fr       */
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
	main_data->tmp = readline("$> ");
	if (main_data->tmp == NULL)
	{
		free(main_data->tmp);
		return (1);
	}
	main_data->line = ft_strtrim(main_data->tmp, " ");
	// main_data->line = main_data->tmp;
	free(main_data->tmp);
	if ((int)main_data->line[0] != 0
		&& same(main_data->history, main_data->line) == 0)
	{
		my_add_history(&main_data->history, ft_strdup(main_data->line));
		add_history(main_data->line);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_main_struct	main_data;

	signal_prepare(&main_data);
	write_to_main_struct(ac, av, envp, &main_data);
	while (1)
	{
		if (check_line(&main_data) == 1)
			break ;
		if (split_main_job(&main_data) == 1)
			break ;
		free(main_data.line);
		main_data.line = NULL;
		rl_on_new_line();
		set_context_string(main_data.line);
		// break;
	}
	ft_lstclear(&main_data.history, del_node);
	ft_lstclear(&main_data.envr, del_node);
	rl_clear_history();
	return (0);
}
// unlink("term"); it was just before return 0;

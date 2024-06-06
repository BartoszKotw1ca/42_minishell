/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:44:28 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/06 10:19:54 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// without readline leaks
// valgrind --leak-check=full --show-leak-kinds=all --suppressions=TMP_TODO/readline.supp ./minishell
// powoduje leaky zwiazane z forkami(child)
// valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --suppressions=TMP_TODO/readline.supp ./minishell

void	ctr_c_sig_handler(int sig)
{
	// printf("%d\n", sig);
	if (sig == 2)
	{
		rl_on_new_line();// without this there wont be $>
		rl_replace_line("", 0); // it might not display correctly the prompt
		write(1, "\n", 1);
		rl_redisplay();// withou it there wont be a prompt
	}
	else if (sig == 3)
	{
		rl_on_new_line();
		rl_replace_line("  ", 0);
		rl_redisplay();
	}
}

int	same(t_list *history, char *line)
{
	t_list	*tmp;
	int		i = 0;

	tmp = history;
	while (tmp && tmp->next)
	{
		i ++;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (0);
	else if (ft_strncmp(tmp->content, line, ft_strlen(line)) == 0)
		return (1);
	return (0);
}

void	update_file(char *name, int content)
{
	int fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_putnbr_fd(content, fd);
	close(fd);
}

char	*read_file(char *name)
{
	char	*res;
	int		fd;

	res = ft_calloc(4, sizeof(char));
	fd = open(name, O_RDONLY);
	read(fd, res, 4);
	close(fd);
	return (res);
}

void	change_directory(char *line)
{
	char	**tmp;
	int		i;
	int		res;

	i = 0;
	tmp = ft_split_except(line, ' ', 39, 34);
	if (ft_strncmp(line, "cd", ft_strlen(line)) == 0)
		res = chdir(getenv("HOME"));
	else if (ft_strncmp(tmp[1], "..", ft_strlen(tmp[1])) == 0)
		res = chdir("..");
	else
		res = chdir(tmp[1]);
	if (res == -1)
		printf("cd: %s: No such file or directory\n", tmp[1]);
	while (tmp[i])
		free(tmp[i ++]);
	free(tmp);
}

int main(int ac, char **av, char **envp)
{
	t_main_struct	main_data;

	(void) ac;
	(void) av;
	update_file("status", '0');
	ft_memset(&(main_data.sa), 0, sizeof(struct sigaction)); // Initialize sa to zero
	main_data.sa.sa_handler = ctr_c_sig_handler; // Set the signal handler
	sigemptyset(&main_data.sa.sa_mask); // Initialize the signal set
	main_data.history = NULL;
	main_data.path = getenv("PATH");
	sigaction(SIGINT, &main_data.sa, NULL); // 2 ctr + c
	sigaction(SIGQUIT, &main_data.sa, NULL); // 3 ctr + "\"
	while (1)
	{
		int	pid = getpid();
		main_data.tmp = readline("$> ");
		if (main_data.tmp == NULL)
		{
			free(main_data.tmp);
			break ;
		}
		main_data.line = ft_strtrim(main_data.tmp, " ");
		free(main_data.tmp);
		if ((int)main_data.line[0] != 0 && same(main_data.history, main_data.line) == 0)
		{
			my_add_history(&main_data.history, ft_strdup(main_data.line));
			add_history(main_data.line);
		}
		if (ft_strncmp(main_data.line, "exit", 4) == 0)
		{
			free(main_data.line);
			break ;
		}
		// else if (ft_strncmp(line, "env", 3) == 0)
		// {
		// 	printf("%s\n", getenv("PATH"));
		// 	free(line);
		// 	exit(0);
		// }
		else if (ft_strncmp(main_data.line, "history", 7) == 0)
		{
			print_history(main_data.history);
			free(main_data.line);
		}
		else if (ft_strncmp(main_data.line, "cd", 2) == 0)
			change_directory(main_data.line);
		else
			split_jobs(main_data.line, main_data.path);
		free(main_data.line);
		// if (line != NULL)
		// 	free(line);
		rl_on_new_line();
	}
	ft_lstclear(&main_data.history, del_node);
	rl_clear_history();
	// unlink("term");
	return 0;
}

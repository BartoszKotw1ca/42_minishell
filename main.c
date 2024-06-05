/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:44:28 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/05 15:14:33 by bkotwica         ###   ########.fr       */
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

int main(int ac, char **av, char **envp) {
	char	*line;
	char	*path;
	char	*tmp;
	int		i = 0;
	t_list	*history;
	// int		terminate;
	struct sigaction sa;

	(void) ac;
	(void) av;
	int j = 0;
	while (envp[j])
		printf("%s\n", envp[j ++]);
	update_file("status", '0');
	ft_memset(&sa, 0, sizeof(struct sigaction)); // Initialize sa to zero
	sa.sa_handler = ctr_c_sig_handler; // Set the signal handler
	sigemptyset(&sa.sa_mask); // Initialize the signal set
	history = NULL;
	path = getenv("PATH");
	sigaction(SIGINT, &sa, NULL); // 2 ctr + c
	sigaction(SIGQUIT, &sa, NULL); // 3 ctr + "\"
	while (1)
	{
		int	pid = getpid();
		tmp = readline("$> ");
		if (tmp == NULL)
		{
			free(tmp);
			break ;
		}
		line = ft_strtrim(tmp, " ");
		free(tmp);
		if ((int)line[0] != 0 && same(history, line) == 0)
		{
			my_add_history(&history, ft_strdup(line));
			add_history(line);
		}
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break ;
		}
		// else if (ft_strncmp(line, "env", 3) == 0)
		// {
		// 	printf("%s\n", getenv("PATH"));
		// 	free(line);
		// 	exit(0);
		// }
		else if (ft_strncmp(line, "history", 7) == 0)
		{
			print_history(history);
			free(line);
		}
		else if (ft_strncmp(line, "cd", 2) == 0)
			change_directory(line);
		else
			split_jobs(line, path);
		free(line);
		// if (line != NULL)
		// 	free(line);
		rl_on_new_line();
	}
	ft_lstclear(&history, del_node);
	rl_clear_history();
	// unlink("term");
	return 0;
}

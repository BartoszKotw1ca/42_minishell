/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:44:28 by bkotwica          #+#    #+#             */
/*   Updated: 2024/05/29 12:27:51 by bkotwica         ###   ########.fr       */
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
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	
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

void	create_term_file(char val)
{
	int fd = open("term", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fd, &val, 1);
	close(fd);
}

int	check_term()
{
	char res;

	int fd = open("term", O_RDONLY);
	read(fd, &res, 1);
	close(fd);
	return (res);
}

int main() {
	char	*line;
	char	*path;
	char	*tmp;
	int		i = 0;
	t_list	*history;
	int		terminate;
	// struct sigaction sa;

	// sa.sa_handler = ctr_c_sig_handler;
	// sa.sa_flags = SA_RESTART;
	// sigaction(2, &sa, NULL);
	create_term_file('0');
	history = NULL;
	path = getenv("PATH");
	while (1)
	{
		if (check_term() == '1')
			break;
		tmp = readline("$> ");
		line = ft_strtrim(tmp, " ");
		free(tmp);
		if ((int)line[0] != 0 && same(history, line) == 0)
		{
			my_add_history(&history, ft_strdup(line));
			add_history(line);
		}
		if (ft_strncmp(line, "exit", 4) == 0)
			create_term_file('1');
		else if (ft_strncmp(line, "history", 7) == 0)
			print_history(history);
		else
			split_jobs(line, path);
		free(line);
	}
	ft_lstclear(&history, del_node);
	rl_clear_history();
	// unlink("term");
	return 0;
}

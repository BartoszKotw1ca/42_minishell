/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:44:28 by bkotwica          #+#    #+#             */
/*   Updated: 2024/05/28 17:51:15 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// without readline leaks
// valgrind --leak-check=full --show-leak-kinds=all --suppressions=TMP_TODO/readline.supp ./minishell

void	ctr_c_sig_handler(int sig)
{
	// printf("%d\n", sig);
	(void)sig;
	write(1, "\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	
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

int main() {
	char	*line;
	char	*path;
	char	*tmp;
	int		i = 0;
	t_list	*history;
	// struct sigaction sa;

	// sa.sa_handler = ctr_c_sig_handler;
	// sa.sa_flags = SA_RESTART;
	// sigaction(2, &sa, NULL);
	history = NULL;
	path = getenv("PATH");
	while (1)
	{
		tmp = readline("$> ");
		line = ft_strtrim(tmp, " ");
		free(tmp);
		if ((int)line[0] != 0 && same(history, line) == 0)
		{
			my_add_history(&history, ft_strdup(line));
			add_history(line);
		}
		if (ft_strncmp(line, "exit", 4) == 0)
			break;
		else if (ft_strncmp(line, "history", 7) == 0)
			print_history(history);
		else
			export_data_to_pipex(line, path);
		free(line);
	}
	ft_lstclear(&history, del_node);
	rl_clear_history();
	return 0;
}

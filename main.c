/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:44:28 by bkotwica          #+#    #+#             */
/*   Updated: 2024/05/28 12:33:53 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// without readline leaks
// valgrind --leak-check=full --show-leak-kinds=all --suppressions=TMP_TODO/readline.supp ./minishell

int main() {
	char	*line;
	char	*path;
	int		i = 0;
	t_list	*history;
	char *tmp;

	history = NULL;
	path = getenv("PATH");
	while (i++ < 2)
	{
		tmp = readline("$> ");
		line = ft_strtrim(tmp, "\t");
		free(tmp);
		add_history(line);
		my_add_history(&history, line);
		if (ft_strncmp(line, "exit", 4) == 0)
			break;
		else if (ft_strncmp(line, "history", 7) == 0)
			print_history(history);
		// printf("%s\n", line);
		export_data_to_pipex(line, path);
		free(line);
	}
	ft_lstclear(&history, del_node);
	rl_clear_history();
	return 0;
}

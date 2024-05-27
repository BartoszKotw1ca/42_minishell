/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:44:28 by bkotwica          #+#    #+#             */
/*   Updated: 2024/05/27 14:15:14 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// without readline leaks
// valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

int main() {
	char *line;
	char	*path;
	int	i = 0;

	path = getenv("PATH");
	while (i++ < 1)
	{
		line = readline("$> ");
		printf("%s\n", line);
		export_data_to_pipex(line, path);
		add_history(line);
		free(line);
	}
	// free(path);
	rl_clear_history();
	return 0;
}

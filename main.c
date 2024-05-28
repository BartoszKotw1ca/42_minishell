/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:44:28 by bkotwica          #+#    #+#             */
/*   Updated: 2024/05/28 13:31:57 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// without readline leaks
// valgrind --leak-check=full --show-leak-kinds=all --suppressions=TMP_TODO/readline.supp ./minishell

int main() {
	char *line;
	char	*path;
	int	i = 0;

	path = getenv("PATH");
	while (i++ < 10)
	{
		line = readline("$> ");
		export_data_to_pipex(line, path);
		add_history(line);
		free(line);
	}
	rl_clear_history();
	return 0;
}

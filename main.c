/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:44:28 by bkotwica          #+#    #+#             */
/*   Updated: 2024/05/27 08:56:45 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig, siginfo_t *info, void *uncontent)
{
	printf("Signal numer: %d, %d, Co tu sie wlasnie stalo???\n", sig, info->si_signo);
	(void) uncontent;
	exit(0);
}

int main() {
    char *line;
    // while compiling we have to add that flag -lreadline
    int	i = 0;
	int	j = 0;
	int	counter = 0;
	struct sigaction sigma;

	sigemptyset(&sigma.sa_mask);
	sigma.sa_flags = SA_SIGINFO;
	sigma.sa_sigaction = signal_handler;
	while (i < 1)
	{
		line = readline("$> ");
		// export_data_to_pipex(line);
		add_history(line);
		            for (j = 0; j < counter; j++) {
                // Simulate history display (can't directly access past commands)
                rl_redisplay(); // "Replay" the user's input
            }
		sigaction(SIGINT, &sigma, NULL);
		// rl_redisplay();
		free(line);
		i ++;
		// printf("%d %s\n", a, name);
	}
    return 0;
}

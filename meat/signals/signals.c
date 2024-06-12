/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:52:36 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/12 11:59:46 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_context_string(void)
{
	static char	*context_string = NULL;
	return (&context_string);
}

void	set_context_string(char *next_context_string)
{
	char	**context_string_ptr = get_context_string();
	*context_string_ptr = next_context_string;
}

void	ctr_c_sig_handler(int sig)
{
	char *context_string = *get_context_string();
	if (sig == 2)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	signal_prepare(t_main_struct *main_data)
{
	ft_memset(&main_data->sa, 0, sizeof(struct sigaction));
	main_data->sa.sa_handler = ctr_c_sig_handler;
	sigemptyset(&main_data->sa.sa_mask);
	sigaction(SIGINT, &main_data->sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

	// sigaction(SIGQUIT, &main_data->sa, NULL);
	// else if (sig == 3)
	// {
	// 	rl_on_new_line();
	// 	rl_redisplay();
	// 	if (context_string != NULL)
	// 		write(1, context_string, ft_strlen(context_string));
	// }

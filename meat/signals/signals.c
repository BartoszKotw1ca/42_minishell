/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:52:36 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/07 15:16:44 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ctr_c_sig_handler(int sig)
{
	if (sig == 2)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
	}
	else if (sig == 3)
	{
		rl_on_new_line();
		rl_replace_line("  ", 0);
		rl_redisplay();
	}
}

void	signal_prepare(t_main_struct *main_data)
{
	ft_memset(&main_data->sa, 0, sizeof(struct sigaction));
	main_data->sa.sa_handler = ctr_c_sig_handler;
	sigemptyset(&main_data->sa.sa_mask);
	sigaction(SIGINT, &main_data->sa, NULL);
	sigaction(SIGQUIT, &main_data->sa, NULL);
}
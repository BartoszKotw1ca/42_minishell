/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:08:20 by jponieck          #+#    #+#             */
/*   Updated: 2024/06/05 18:57:08 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_data *data)
{
	int	i;


	i = 0;
	while (data->envr)
	{
		printf("env --- %s\n", (char *)data->envr->content);
		data->envr = data->envr->next;
	}
}

void	set_env(t_data *data, char **envp)
{
	int	i;

	data->envr = NULL;
	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&data->envr, ft_lstnew(envp[i]));
		i++;
	}
	print_env(data);
}

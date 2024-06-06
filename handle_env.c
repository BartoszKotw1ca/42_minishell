/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:08:20 by jponieck          #+#    #+#             */
/*   Updated: 2024/06/05 22:10:45 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_env(t_data *data, char *key)
{
	t_list	*start;
	char	*value;

	start = data->envr;
	value = NULL;
	while (data->envr)
	{
		if (ft_strnstr(data->envr->content, key, ft_strlen(key)))
			value = ft_strchr(data->envr->content, '=') + 1;
		data->envr = data->envr->next;
	}
	data->envr = start;
	return (value);
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
}

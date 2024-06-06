/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:08:20 by jponieck          #+#    #+#             */
/*   Updated: 2024/06/06 19:02:29 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_env(t_main_struct *main_data, char *key)
{
	t_list	*start;
	char	*value;

	start = main_data->envr;
	value = NULL;
	while (main_data->envr)
	{
		if (ft_strnstr(main_data->envr->content, key, ft_strlen(key)))
			value = ft_strchr(main_data->envr->content, '=') + 1;
		main_data->envr = main_data->envr->next;
	}
	main_data->envr = start;
	return (value);
}

void	update_env(t_main_struct *main_data, char *key, char *value)
{
	t_list	*start;
	char	*new_content;
	char	*temp;
	int		found;

	found = 0;
	temp = ft_strjoin(key, "=");
	new_content = ft_strjoin(temp, value);
	free(temp);
	start = main_data->envr;
	while (main_data->envr)
	{
		if (ft_strnstr(main_data->envr->content, key, ft_strlen(key)))
		{
			free(main_data->envr->content);
			main_data->envr->content = new_content;
			found = 1;
		}
		main_data->envr = main_data->envr->next;
	}
	if (found == 0)
		ft_lstadd_back(&main_data->envr, ft_lstnew(new_content));
	main_data->envr = start;
}

void	set_env(t_main_struct *main_data, char **envp)
{
	int	i;

	main_data->envr = NULL;
	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&main_data->envr, ft_lstnew(envp[i]));
		i++;
	}
}

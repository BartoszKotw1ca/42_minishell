/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:08:20 by jponieck          #+#    #+#             */
/*   Updated: 2024/06/09 15:30:37 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset_env(t_main_struct *main_data, char *key)
{
	t_list	*start;
	t_list	*prev;

	start = main_data->envr;
	prev = NULL;
	while (main_data->envr)
	{
		if (ft_strnstr(main_data->envr->content, key, ft_strlen(key)))
		{
			if (((char *)main_data->envr->content)[ft_strlen(key)] == '=');
			{
				if (prev)
					prev->next = main_data->envr->next;
				else
					start = main_data->envr->next;
				free(main_data->envr->content);
				free(main_data->envr);
				main_data->envr = start;
				return ;
			}
		}
		prev = main_data->envr;
		main_data->envr = main_data->envr->next;
	}
	main_data->envr = start;
}

char	*read_env(t_main_struct *main_data, char *key)
{
	t_list	*start;
	char	*value;
	int		key_len;

	start = main_data->envr;
	value = NULL;
	key_len = ft_strlen(key);
	key[key_len] = '='; 
	while (main_data->envr)
	{
		// if (ft_strnstr(main_data->envr->content, key, ft_strlen(key)))
		if (ft_strncmp(main_data->envr->content, key, key_len + 1) == 0)
		{
			value = ft_strchr(main_data->envr->content, '=');
			if (value)
				value ++;
		}
		main_data->envr = main_data->envr->next;
	}
	main_data->envr = start;
	return (value);
}

void	print_env(t_main_struct *main_data)
{
	t_list	*start;

	start = main_data->envr;
	while (main_data->envr)
	{
		printf("%s\n", (char *)main_data->envr->content);
		main_data->envr = main_data->envr->next;
	}
	main_data->envr = start;
}

void	export_env(t_main_struct *main_data, char *key_val)
{
	t_list	*start;
	int		val_index;
	int		found;
	char	*key;

	found = 0;
	start = main_data->envr;
	val_index = ft_strchr(key_val, '=') - key_val;
	while (main_data->envr)
	{
		if (ft_strncmp((char *)main_data->envr->content, key_val, val_index) == 0)
		{
			if (((char *)main_data->envr->content)[val_index] == '=' || ((char *)main_data->envr->content)[val_index] == 0)
			{
				free(main_data->envr->content);
				main_data->envr->content = ft_strdup(key_val);
				found = 1;
			}
		}
		main_data->envr = main_data->envr->next;
	}
	main_data->envr = start;
	if (found == 0)
		ft_lstadd_back(&main_data->envr, ft_lstnew(ft_strdup(key_val)));
}
// BK i dont konw if it is correct, but there is no leak free(key)

void	set_env(t_main_struct *main_data, char **envp)
{
	int	i;

	main_data->envr = NULL;
	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&main_data->envr, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
}
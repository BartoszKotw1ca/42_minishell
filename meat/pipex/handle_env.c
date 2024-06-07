/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:08:20 by jponieck          #+#    #+#             */
/*   Updated: 2024/06/07 15:17:24 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	key = calloc(val_index + 1, sizeof(char));
	ft_strlcpy(key, key_val, val_index + 1);
	while (main_data->envr)
	{
		if (ft_strnstr((char *)main_data->envr->content, key, val_index))
		{
			free(main_data->envr->content);
			main_data->envr->content = ft_strdup(key_val);
			found = 1;
		}
		main_data->envr = main_data->envr->next;
	}
	main_data->envr = start;
	if (found == 0)
		ft_lstadd_back(&main_data->envr, ft_lstnew(ft_strdup(key_val)));
	free(key);
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

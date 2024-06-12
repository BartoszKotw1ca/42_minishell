/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_and_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:16:09 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/12 07:55:43 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_inside_export(t_main_struct *main_data, int j)
{
	while (main_data->ted[main_data->i][j]
		&& (ft_isalnum(main_data->ted[main_data->i][j]) == 1
		|| main_data->ted[main_data->i][j] == '='
		|| main_data->ted[main_data->i][j] == '$'
		|| main_data->ted[main_data->i][j] == '_'))
		j ++;
	if (main_data->ted[main_data->i][j] == '\0')
	{
		j = 1;
		while (main_data->ted[main_data->i][j]
			&& main_data->ted[main_data->i][j] != '=')
			j ++;
		if (main_data->ted[main_data->i][j] != '\0')
			export_env(main_data, main_data->ted[main_data->i]);
	}
	else
		printf("export: \'%s\': not a valid identifier\n",
			main_data->ted[main_data->i]);
}

void	check_for_export(t_main_struct *main_data)
{
	int	j;

	main_data->i = 1;
	while (main_data->ted[main_data->i])
	{
		j = 0;
		if (ft_isalnum(main_data->ted[main_data->i][j]) == 0
			|| main_data->ted[main_data->i][j] == '_')
			printf("export: \'%s\': not a valid identifier\n",
				main_data->ted[main_data->i]);
		else
		{
			j ++;
			check_inside_export(main_data, j);
		}
		main_data->i ++;
	}
}

void	initialize_export(t_main_struct *main_data)
{
	main_data->ted = ft_split(main_data->line, ' ');
	check_for_export(main_data);
	main_data->i = 0;
	while (main_data->ted[main_data->i])
		free(main_data->ted[main_data->i ++]);
	free(main_data->ted);
}

void	initialize_unset(t_main_struct *main_data)
{
	main_data->ted = ft_split(main_data->line, ' ');
	main_data->i = 1;
	while (main_data->ted[main_data->i])
	{
		unset_env(main_data, main_data->ted[main_data->i]);
		main_data->i ++;
	}
	main_data->i = 0;
	while (main_data->ted[main_data->i])
		free(main_data->ted[main_data->i ++]);
	free(main_data->ted);
}

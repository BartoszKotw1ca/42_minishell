/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_data_to_pipex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:38 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/07 15:17:50 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// that file contains the functions that should write data from line
// to our t_data structure

int	tmp_fun(t_data *data)
{
	if (!data->tmp)
		data = data_for_null(data, data->tmp);
	else if (data->tmp[0][0] == '<' && data->tmp[1][0] == '<')
	{
		printf("%s", "parse error near \'<\'");
		return (0);
	}
	else
	{
		write_to_infile(data->tmp, data);
		write_to_outfile(data->tmp, data, 0, 0);
		process_data(data->tmp, data, 0);
		count_commnads(data);
	}
	return (1);
}

void	export_data_to_pipex(char *argv, char *path, t_main_struct *main_data)
{
	t_data	data;
	char	*line;

	if ((int)argv[0] == 0)
		return ;
	if (check_the_line(argv, &data) == 1)
	{
		line = change_line(&data, argv, check_the_line(argv, &data));
		free(argv);
		argv = line;
	}
	data.tmp = ft_split(argv, ' ');
	if (tmp_fun(&data) == 0)
		return ;
	data.paths = ft_split(path, ':');
	check_infile(&data);
	mini_pipex(&data, main_data);
	free_dataa(&data, data.tmp);
}

// free(argv); the last command

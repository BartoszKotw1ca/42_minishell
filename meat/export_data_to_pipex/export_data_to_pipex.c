/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_data_to_pipex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:38 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/20 10:18:27 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// that file contains the functions that should write data from line
// to our t_data structure

t_data	*new_one(t_data *data);

int	tmp_fun(t_data *data)
{
	if (!data->tmp)
		data = data_for_null(data);
	else if (data->tmp[0][0] == '<' && data->tmp[1][0] == '<')
	{
		free_split(data->tmp);
		print_error("Bad command, cowboy!", "parse error near \'<\'\n");
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

void	free_after_mixed(t_data *data_tmp, t_data *data, char *argv)
{
	int	i;

	i = 0;
	while (i < data_tmp->num_of_com)
		free(data_tmp->com[i ++].commend);
	i = 0;
	(void) argv;
	i = -1;
	while (++ i < data->num_of_com)
		if (data->com[i].infile)
			free(data->com[i].infile);
	i = -1;
	while (++ i < data->num_of_com)
		if (data->com[i].outfile)
			free(data->com[i].outfile);
	free(data_tmp->com);
	i = -1;
	while (data->her[++ i])
	{
		if (access(data->her[i], F_OK) == 0)
			unlink(data->her[i]);
		free(data->her[i]);
	}
	free(data->her);
}

void	run_mini_pi(t_data *data, char *argv, t_main_struct *main_data)
{
	t_data	*data_tmp;

	data->paths = get_path(main_data);
	check_infile(data);
	if (data->num_of_com == data->pipes_counter)
	{
		data_tmp = new_one(data);
		if (check_inside_red(data_tmp) == 0 && data_tmp != NULL)
			mini_pipex(data_tmp, main_data);
		else
			print_error("Bad command, cowboy!", "Maybe next time!\n");
		free_after_mixed(data_tmp, data, argv);
	}
	else
		print_error("Bad command, cowboy!", "Maybe next time!\n");
	free_dataa(data, data->tmp);
}

void	write_new_data(t_data *data, int i, int li, char **te)
{
	if (i != data->num_of_com - 1 && i != data->num_of_com)
	{
		if (li == 0)
			data->com[i].mode = -1;
		else if (li == 1)
			data->com[i].mode = 1;
		else
			data->com[i].mode = 0;
	}
	free_splited_list(data->commends);
	process_data(te, data, 0);
	data->com[i].commend = ft_strdup(data->commends[0]);
	if (i != 0)
		data->com[i].infile = ft_strdup(data->infile);
	if (i != data->num_of_com - 1)
		data->com[i].outfile = ft_strdup(data->outfile);
	free_splited_list(te);
}

void	export_data_to_pipex(char *argv, t_main_struct *main_data)
{
	t_data	data;
	char	*line;
	int		tmp;

	tmp = 0;
	data = (t_data){0};
	if ((int)argv[0] == 0)
		return ;
	count_pipes(&data, argv);
	if (check_the_line(argv, &data) == 1)
	{
		tmp = 1;
		line = change_line(argv);
		argv = ft_strdup(line);
		free(line);
	}
	else if (check_the_line(argv, &data) == 0)
		data.mode = -1;
	data.tmp = split_ex(argv, ' ', 39, 34);
	if (tmp_fun(&data) == 0)
		return ;
	run_mini_pi(&data, argv, main_data);
	if (tmp == 1)
		free(argv);
}

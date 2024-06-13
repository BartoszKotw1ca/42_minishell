/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_data_to_pipex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:38 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/13 10:53:28 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// that file contains the functions that should write data from line
// to our t_data structure

t_data	*new_one(t_data *data);

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

char	skip_spaces_back(char *str, int index)
{
	while (index >= 0 && str[index] == ' ')
		index--;
	if (index >= 0)
		return (str[index]);
	else
		return ('\0');
}

int	check_line1(char *argv)
{
	int	i;

	i = strlen(argv) - 1;
	while (i >= 0 && argv[i] != '|')
	{
		if (argv[i] == '>' && i - 1 >= 0 && argv[i - 1] == '>')
			return (1);
		else if (argv[i] == '>' && skip_spaces_back(argv, i - 1) != '\0')
			return (2);
		else
			i--;
	}
	return (0);
}

void	free_after_mixed(t_data *data_tmp, t_data *data, char *argv)
{
	int	i;

	i = 0;
	while (i < data_tmp->num_of_com)
		free(data_tmp->com[i ++].commend);
	i = 0;
	if (data->mode == 1)
		free(argv);
	if (access("heredoc.txt", F_OK) == 0)
		unlink("heredoc.txt");
	i = -1;
	while (++ i < data->num_of_com)
		if (data->com[i].infile)
			free(data->com[i].infile);
	i = -1;
	while (++ i < data->num_of_com)
		if (data->com[i].outfile)
			free(data->com[i].outfile);
	free(data_tmp->com);
}

int	check_inside_red(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_com)
	{
		if (data->com[i].commend == NULL)
			return (1);
		i ++;
	}
	return (0);
}

void	run_mini_pi(t_data *data_tmp, t_data *data, char *path, char *argv)
{
	data->paths = ft_split(path, ':');
	check_infile(data);
	int	i = 0;
	while (data->commends[i])
		printf("com: %s\n", data->commends[i ++]);
	// exit(0);
	if (data->num_of_com == data->pipes_counter)
	{
		int i = -1;
		data_tmp = new_one(data);
		if (check_inside_red(data_tmp) == 0 && data_tmp != NULL)
			while (++ i < data_tmp->num_of_com)
				printf("commmm: %s, infile: %s, outfile: %s, mode: %d\n", data_tmp->com[i].commend, data_tmp->com[i].infile, data_tmp->com[i].outfile, data_tmp->com[i].mode);
			// mini_pipex(data_tmp, main_data); // should take the data_tmp
		else
			printf("%s", "Bad command, cowboy!\nMaybe next time!\n");
		free_after_mixed(data_tmp, data, argv);
	}
	else
	{
		// if (argv)
		// 	free(argv);
		printf("%s", "Bad command, cowboy!\nMaybe next time!\n");
	}
	free_dataa(data, data->tmp);
}

void	count_pipes(t_data *data, char *argv)
{
	int		i;
	int		doubl;
	int		one;

	i = -1;
	doubl = 0;
	one = 0;
	data->pipes_counter = 1;
	while (argv[++ i])
	{
		if (argv[i] == 39 && one == 0)
			one = 1;
		else if (argv[i] == 34 && doubl == 0)
			doubl = 1;
		else if (argv[i] == 39 && one == 1)
			one = 0;
		else if (argv[i] == 34 && doubl == 1)
			doubl = 0;
		else if (argv[i] == '|' && one == 0 && doubl == 0)
			data->pipes_counter += 1;
	}
}

void	export_data_to_pipex(char *argv, char *path, t_main_struct *main_data)
{
	t_data	data;
	char	*line;
	t_data	*data_tmp;

	if ((int)argv[0] == 0)
		return ;
	count_pipes(&data, argv);
	if (check_the_line(argv, &data) == 1)
	{
		line = change_line(&data, argv, check_the_line(argv, &data));
		// free(argv);
		argv = ft_strdup(line);
		free(line);
	}
	else if (check_the_line(argv, &data) == 0)
		data.mode = -1;
	data.tmp = ft_split(argv, ' ');
	if (tmp_fun(&data) == 0)
		return ;
	run_mini_pi(data_tmp, &data, path, argv);
}

void	free_splited_list(char **tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
		free(tmp[i ++]);
	free(tmp);
}

//////////////////////////////////////////////////////////////////////////////
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

void	write_out(t_data *data, int i, int li, char **te)
{
	char	*e;
	char	*t;

	if (i != data->num_of_com - 1)
	{
		free(data->outfile);
		if (li == 1)
		{
			t = ft_listjoin(0, data->end, te);
			e = change_line(data, t, 1);
			free(t);
			free_splited_list(te);
			te = ft_split(e, ' ');
			free(e);
		}
		write_to_outfile(te, data, 0, 0);
	}
}

int	check_for_red(char **tmp_com, int i)
{
	char	*res;

	if (tmp_com[i][1] == '<' && tmp_com[i][2] == '<')
	{
		if (check_if_ok(tmp_com[i], 3) == 1)
			return (1);
		else
		{
			res = write_to_file(tmp_com[i]);
			if (res == NULL)
				return (1);
			free(tmp_com[i]);
			tmp_com[i] = ft_strdup(res);
			free(res);
		}
	}
	return (0);
}

void	write_in(t_data *data, int i, char **te)
{
	int	p;

	p = 0;
	while (te[p])
		p ++;
	data->end = p - 1;
	if (i != 0)
	{
		free(data->infile);
		write_to_infile(te, data);
	}
}

void	initialize_values(t_data *data)
{
	data->com = malloc(sizeof(t_com) * data->num_of_com);
	data->com[0].infile = ft_strdup(data->infile);
	data->com[data->num_of_com - 1].outfile = ft_strdup(data->outfile);
	data->com[data->num_of_com - 1].mode = data->mode;
	data->start = 0;
}

// free(argv); the last command
//=====================
t_data	*new_one(t_data *data)
{
	char	**tmp_com;
	char	**te;
	int		i;
	int		li;

	tmp_com = NULL;
	tmp_com = malloc(sizeof(char *) * (data->num_of_com + 1));
	i = -1;
	while (data->commends[++ i])
		tmp_com[i] = ft_strdup(data->commends[i]);
	tmp_com[i] = NULL;
	initialize_values(data);
	i = -1;
	while (tmp_com[++ i])
	{
		if (check_for_red(tmp_com, i) != 0)
			return (NULL);
		te = ft_split(tmp_com[i], ' ');
		write_in(data, i, te);
		li = check_line1(tmp_com[i]);
		write_out(data, i, li, te);
		write_new_data(data, i, li, te);
	}
	free_splited_list(tmp_com);
	return (data);
}

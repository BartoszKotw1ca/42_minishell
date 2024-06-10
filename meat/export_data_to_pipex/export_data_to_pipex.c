/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_data_to_pipex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:38 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/10 22:29:19 by jponieck         ###   ########.fr       */
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

char skip_spaces_back(char *str, int index)
{
    while (index >= 0 && str[index] == ' ')
        index--;
    if (index >= 0)
        return str[index];
    else
        return '\0';
}

int    check_line1(char *argv)
{
    int    i;

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

void	export_data_to_pipex(char *argv, char *path, t_main_struct *main_data)
{
	t_data	data;
	char	*line;
	t_data	*data_tmp;

	if ((int)argv[0] == 0)
		return ;
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
	data.paths = ft_split(path, ':');
	check_infile(&data);
	data_tmp = new_one(&data);
	
	// mini_pipex(&data_tmp, main_data); // should take the data_tmp
	int i = -1;
	while (++i < data_tmp->num_of_com)
		printf("com: %s, infile: %s, outfile: %s, mode: %d\n", data_tmp->com[i].commend, data_tmp->com[i].infile, data_tmp->com[i].outfile, data_tmp->com[i].mode);
	// first check that it will show you the names and how it looks like :)
	// and there should not be any leaks
	free_dataa(&data, data.tmp);
	free(data_tmp->com[data_tmp->num_of_com - 1].outfile);
	i = 0;
	while (i < data_tmp->num_of_com)
		free(data_tmp->com[i ++].commend);
	i = 0;
	free(data_tmp->com);
	if (data.mode == 1)
		free(argv);
}

// free(argv); the last command

t_data	*new_one(t_data *data)
{
	t_data *tmp = data;
	char **tmp_com = data->commends;
	int i = tmp->num_of_com;
	tmp_com = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (tmp->commends[++ i])
		tmp_com[i] = ft_strdup(tmp->commends[i]);
	tmp_com[i] = NULL;
	tmp->com = malloc(sizeof(t_com) * tmp->num_of_com);
	i = 0;
	tmp->com[i].infile = tmp->infile;
	tmp->com[tmp->num_of_com - 1].outfile = ft_strdup(tmp->outfile);
	tmp->com[tmp->num_of_com - 1].mode = tmp->mode;
	tmp->start = 0;
	while (tmp_com[i]) {;
		char	**te = ft_split(tmp_com[i], ' ');
		int	p = 0;
		while (te[p])
			p ++;
		tmp->end = p - 1;
		if (i != 0)
		{
			free(tmp->infile);
			write_to_infile(te, tmp);
		}
		int	li = check_line1(tmp_com[i]);
		if (i != tmp->num_of_com - 1)
		{
			free(tmp->outfile);
			if (li == 1)
			{
				char *t = ft_listjoin(0, tmp->end, te);
				char *e = change_line(tmp, t, 1);
				free(t);
				int u = 0;
				while (te[u])
					free(te[u ++]);
				free(te);
				te = ft_split(e, ' ');
				free(e);
			}
			write_to_outfile(te, tmp, 0, 0);
		}
		if (i != tmp->num_of_com - 1 && i != tmp->num_of_com)
		{
			if (li == 0)
				tmp->com[i].mode = -1;
			else if (li == 1)
				tmp->com[i].mode = 1;
			else
				tmp->com[i].mode = 0;
		}
		int e = 0;
		e = 0;
		while (tmp->commends[e])
			free(tmp->commends[e ++]);
		free(tmp->commends);
		process_data(te, tmp, 0);
		tmp->com[i].commend = ft_strdup(tmp->commends[0]);
		if (i != 0)
			tmp->com[i].infile = tmp->infile;
		if (i != tmp->num_of_com - 1)
			tmp->com[i].outfile = tmp->outfile;
		e = 0;
		while (te[e])
			free(te[e ++]);
		free(te);
		// printf("commend: %s, infile: %s, outfile: %s, mode: %d\n", tmp->com[i].commend, tmp->com[i].infile, tmp->com[i].outfile, tmp->com[i].mode);
		i ++;
	}
	i = 0;
	while (tmp_com[i])
		free(tmp_com[i ++]);
	free(tmp_com);
	return (tmp);
}

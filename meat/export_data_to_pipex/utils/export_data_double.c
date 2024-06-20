/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_data_double.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:05:59 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/20 10:11:52 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
			e = change_line(t);
			free(t);
			free_splited_list(te);
			te = split_ex(e, ' ', 39, 34);
			free(e);
		}
		write_to_outfile(te, data, 0, 0);
	}
}

int	check_for_red(t_data *data, char **tmp_com, int i, int j)
{
	char	*res;

	if (tmp_com[i][1] == '<' && tmp_com[i][2] == '<')
	{
		if (check_if_ok(tmp_com[i], 3) == 1)
			return (1);
		else
		{
			while (data->her[j])
				j++;
			data->her[j ++] = name_of_heredoc("heredoc0");
			data->her[j] = NULL;
			res = write_to_file(tmp_com[i], data->her[j - 1]);
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
	data->her = malloc(sizeof(char *) * 9);
	data->her[0] = NULL;
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
		if (check_for_red(data, tmp_com, i, 0) != 0)
			return (NULL);
		te = split_ex(tmp_com[i], ' ', 39, 34);
		write_in(data, i, te);
		li = check_line1(tmp_com[i]);
		write_out(data, i, li, te);
		write_new_data(data, i, li, te);
	}
	free_splited_list(tmp_com);
	return (data);
}

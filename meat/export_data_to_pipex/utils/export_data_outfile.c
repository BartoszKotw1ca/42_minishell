/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_data_outfile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:58:43 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/07 15:18:03 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_if_zero(int *i, t_data *data, int j, char **tmp)
{
	(*i)--;
	if (*i == 0)
	{
		data->outfile = NULL;
		data->end = 0;
		return (-1);
	}
	while (tmp[*i - 1][j])
		j ++;
	return (j);
}

void	write_to_outfile(char **tmp, t_data *data, int i, int j)
{
	while (tmp[i])
		i ++;
	j = check_if_zero(&i, data, 0, tmp);
	if (j == -1)
		return ;
	if (tmp[i - 1][0] == '>' && tmp[i - 1][1] == '\0')
	{
		data->outfile = write_to(tmp[i], ft_strlen(tmp[i]));
		data->end = i - 2;
	}
	else if (tmp[i][0] == '>' && tmp[i][1] != '\0')
	{
		data->outfile = write_to(&tmp[i][1], ft_strlen(&tmp[i][1]));
		data->end = i - 1;
	}
	else if (tmp[i - 1][j - 1] == '>' && tmp[i - 1][j] == '\0')
	{
		data->outfile = write_to(tmp[i], ft_strlen(tmp[i]));
		data->end = i -1;
	}
	else
	{
		in_the_middle(tmp, data, i, 0);
		data->end = i;
	}
}

void	process_data(char **tmp, t_data *data, int j)
{
	char	*line;

	while (tmp[data->end][j])
		j ++;
	if (tmp[data->end][j - 1] == '>')
		tmp[data->end][j - 1] = '\0';
	line = ft_listjoin(data->start, data->end, tmp);
	data->commends = ft_split(line, '|');
	free(line);
}

char	*change_line(t_data *data, char *argv, int check)
{
	int		i;
	char	*line;
	int		j;

	j = 0;
	i = -1;
	line = malloc(sizeof(char) * ft_strlen(argv));
	line[ft_strlen(argv) - 1] = '\0';
	while (argv[++ i])
	{
		if (argv[i] == '>')
			i ++;
		line[j ++] = argv[i];
	}
	return (line);
}

void	in_the_middle(char	**tmp, t_data *data, int i, int j)
{
	char	*temp;
	int		tm;

	tm = 0;
	while (tmp[i][j])
		if (tmp[i][j ++] == '>')
			break ;
	if (tmp[i][j - 1] == '>')
	{
		tm = j;
		while (tmp[i][tm])
			tm ++;
		temp = malloc(sizeof(char) * (tm - j + 1));
		temp[tm - j] = '\0';
		tm = 0;
		while (tmp[i][j])
			temp[tm++] = tmp[i][j ++];
		tmp[i][ft_strlen(tmp[i]) - ft_strlen(temp)] = '\0';
		data->outfile = temp;
	}
	else
		data->outfile = NULL;
}
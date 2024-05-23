/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_data_to_pipex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:38 by bkotwica          #+#    #+#             */
/*   Updated: 2024/05/23 16:40:24 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*write_to(char *str, int len)
{
	char	*res;
	int		i;

	i = -1;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (str[++i])
		res[i] = str[i];
	return (res);
}

void	write_to_infile(char **tmp, t_data *data)
{
	if (tmp[0][0] == '<' && tmp[0][1] == '\0')
	{
		data->infile = write_to(tmp[1], ft_strlen(tmp[1]));
		data->start = 2;
	}
	else if (tmp[0][0] == '<' && tmp[0][1] != '\0')
	{
		data->infile = write_to(&tmp[0][1], ft_strlen(&tmp[0][1]));
		data->start = 1;
	}
	else
	{
		data->infile = NULL;
		data->start = 0;
	}
}

void	in_the_middle(char	**tmp, t_data *data, int i, int j)
{
	char	*temp;
	int		tm;

	tm = 0;
	while (tmp[i][j])
		if (tmp[i][j ++] == '>')
			break;
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

void	write_to_outfile(char **tmp, t_data *data, int i, int j)
{
	while (tmp[i])
		i ++;
	i --;
	while (tmp[i - 1][j])
		j ++;
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
	printf("%s", line);
	data->commends = ft_split(line, '|');
	free(line);
}

t_data	export_data_to_pipex(char *argv)
{
	t_data	data;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(argv, ' '); // freee it
	write_to_infile(tmp, &data);
	write_to_outfile(tmp, &data, 0, 0);
	process_data(tmp, &data, 0);
	while (tmp[i])
		free(tmp[i ++]);
	free(tmp);
	return (data);
}

int	main(void)
{
	t_data	data;
	int		i;

	i = 0;
	data = export_data_to_pipex("      < janek.txt cat | grep kot | awk '{print }' | cmd4 > end.txt");
	printf("start: %d\nend: %d\n", data.start, data.end);
	printf("data.infile = %s\ndata.outfile = %s\n",
		data.infile, data.outfile);
	while (data.commends[i])
		printf("com: %s \n", data.commends[i ++]);
	// that is the part which free all the memory
	i = 0;
	free(data.infile);
	free(data.outfile);
	while (data.commends[i])
		free(data.commends[i ++]);
	free(data.commends);
}

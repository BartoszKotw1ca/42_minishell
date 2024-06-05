/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_data_to_pipex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:38 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/05 18:16:16 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// that file contains the functions that should write data from line
// to our t_data structure

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

int	check_if_zero(int *i, t_data *data, int j, char **tmp)
{
	(*i) --;
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

void	count_commnads(t_data *data)
{
	int	res;

	res = 0;
	while (data->commends[res])
		res++;
	data->num_of_com = res;
}

void	free_dataa(t_data *data, char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		free(tmp[i ++]);
	free(tmp);
	free(data->infile);
	free(data->outfile);
	i = 0;
	if (data->commends)
	{
		while (data->commends[i])
			free(data->commends[i ++]);
	}
	free(data->commends);
	i = 0;
	if (data->commends)
	{
		while (data->paths[i])
			free(data->paths[i ++]);
	}
	free(data->paths);
}

t_data	*data_for_null(t_data *data, char **tmp)
{
	data->infile = NULL;
	data->outfile = NULL;
	data->start = 0;
	data->end = 0;
	data->commends = NULL;
	data->num_of_com = 0;
	data->paths = NULL;
	return (data);
}

char	skip_spaces(char *argv, int i)
{
	while (argv[i] && argv[i] == ' ')
		i ++;
	return (argv[i]);
}

int	check_the_line(char *argv, t_data *data)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '>' && argv[i + 1] && argv[i + 1] == '>')
		{
			data->mode = 1;
			return (1);
		}
		else if (argv[i] == '>' && skip_spaces(&argv[i], i) != '\0')
		{
			data->mode = 0;
			return (2);
		}
		else
			i ++;
	}
	return (0);
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

void	check_infile(t_data *data)
{
	if (!data->infile)
		return ;
	data->infile_ok = 0;
	if (access(data->infile, F_OK) != 0)
	{
		print_error(data->infile, "no such file\n");
		data->infile_ok = -1;
	}
	else if (access(data->infile, R_OK) != 0)
	{
		print_error(data->infile, "permision denied\n");
		data->infile_ok = -1;
	}
}

void	export_data_to_pipex(char *argv, char *path, char **envp)
{
	t_data	data;
	char	**tmp;
	int		i;

	i = 0;
	if ((int)argv[0] == 0)
		return ;
	if (check_the_line(argv, &data) == 1)
	{
		char	*line;
		line =  change_line(&data, argv, check_the_line(argv, &data));
		free(argv);
		argv = line;
	}
	tmp = ft_split_except(argv, ' ', 39, 34);
	if (!tmp)
		data = *data_for_null(&data, tmp);
	else if (tmp[0][0] == '<' && tmp[1][0] == '<')
	{
			printf("%s", "parse error near \'<\'");
			return ;
	}
	else
	{
		write_to_infile(tmp, &data);
		write_to_outfile(tmp, &data, 0, 0);
		process_data(tmp, &data, 0);
		count_commnads(&data);
	}
	data.paths = ft_split(path, ':');
	check_infile(&data);
	set_env(&data, envp);
	mini_pipex(&data);
	free_dataa(&data, tmp);
	// free(argv);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	data;
// 	int		i;
// 	int		pid;

// 	i = 0;
// 	(void) envp;
// 	data = export_data_to_pipex(argv[1], "PATH=/nfs/homes/bkotwica/bin:/nfs/homes/bkotwica/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin");
// 	printf("start: %d\nend: %d\n", data.start, data.end);
// 	printf("Num of comm: %d\n", data.num_of_com);
// 	printf("data.infile = %s\ndata.outfile = %s\n",
// 		data.infile, data.outfile);
// 	if (data.commends != NULL)
// 	{
// 		while (data.commends[i])
// 			printf("com: %s \n", data.commends[i ++]);
// 	}
// 	printf("\n---- mini pipex starts here ----\n");
// 	printf("↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓\n\n");
// 	mini_pipex(&data);
// 	// that is the part which free all the memory
// 	i = 0;
// 	free(data.infile);
// 	free(data.outfile);
// 	if (data.commends)
// 	{
// 		while (data.commends[i])
// 			free(data.commends[i ++]);
// 		// free(data.commends);
// 	}
// 	// while (data.commends[i])
// 	// 	free(data.commends[i ++]);
// 	free(data.commends);
// 	i = 0;
// 	if (data.commends)
// 	{
// 		while (data.paths[i])
// 			free(data.paths[i ++]);
// 	}
// 	free(data.paths);
// }

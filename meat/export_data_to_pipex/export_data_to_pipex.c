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

int    check_line1(char *argv) {
	int    i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '>' && argv[i + 1] && argv[i + 1] == '>')
			return (1);
		else if (argv[i] == '>')
			if (skip_spaces(&argv[i], i + 1) != '\0')
				return (2);
		i ++;
	}
	return (0);
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
	else
		data.mode = -1;
	data.tmp = ft_split(argv, ' ');
	if (tmp_fun(&data) == 0)
		return ;
	data.paths = ft_split(path, ':');
	check_infile(&data);

	// printf("%s\n", data.infile);
	// printf("%s\n", data.outfile);
	printf("%d", check_line1(data.commends[1]));
	printf("%s", data.commends[1]);
	exit(0);
	int j = 0;
	printf("%d\n", data.mode);
	data.com = malloc(sizeof(t_com) * data.num_of_com);
	int i = 0;
	data.com[i].infile = ft_strdup(data.infile);
	data.com[i].outfile = ft_strdup(data.outfile);
	while (data.commends[i]) {
		char	**te = ft_split(data.commends[i], ' ');
		// da.mode = -1;
		write_to_infile(te, &data);
		write_to_outfile(te, &data, 0, 0);
		int	li = check_the_line(data.commends[i], &data);
		if (li == 0)
			data.com[i].mode = -1;
		else if (li == 1)
			data.com[i].mode = 1;
		else
			data.com[i].mode = 0;
		data.com[i].commend = ft_strdup(data.commends[i]);
		data.com[i].infile = ft_strdup(data.infile);
		data.com[i].outfile = ft_strdup(data.outfile);
		// data.com[i].mode = data.mode;
		i ++;
	}
	// exit (0);
	i = -1;
	// char **te = ft_split(data.commends[i], ' ');
	// write_to_infile(te, data.com[0]);
	while (++i < data.num_of_com)
		printf("%d : %s : %s : %s\n", data.com[i].mode, data.com[i].commend, data.com[i].infile, data.com[i].outfile);
	exit(0);
	// printf("%s %s", maininfile, mainoutfile);
	// char **te = ft_split(data.commends[1], ' ');
	// write_to_infile(te, &data);
	// write_to_outfile(te, &data, 0, 0);
	// printf("%s\n", data.infile);
	// printf("%s\n", data.outfile);

	// int	i = 0;
	// data.com = malloc(sizeof(t_com) * data.num_of_com);
	// data.com[0].commend = "tak";
	// printf("%s", data.com[0].commend);
	// data.com[1].commend = "nie";
	// printf("\n%s", data.com[1].commend);
	// free(data.com);

	// while (data.commends[i]) {
	// 	data.com.commend = ft_strdup(data.commends[i]);
	// 	printf("%s\n", data.com.commend);
	// 	exit(0);
	// }

	// mini_pipex(&data, main_data);
	free_dataa(&data, data.tmp);
}

// free(argv); the last command

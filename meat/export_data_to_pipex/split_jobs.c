/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:26:44 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/11 19:10:31 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*tmp_fun_write_to_file(int len_list,
	char **splited_line, int fd, char *get_next)
{
	// (void) len_list;
	close(fd);
	fd = open("heredoc.txt", O_RDONLY);
	get_next = get_next_line(fd);
	while (get_next)
	{
		printf("%s", get_next);
		free(get_next);
		get_next = get_next_line(fd);
	}
	free(get_next);
	close(fd);
	unlink("heredoc.txt");
	free_list(splited_line, fd, 0, 0);
	return (NULL);
}

// write to file the lines after << "something"
char	*write_to_file(char *line)
{
	char	**splited_line;
	char	*linee;
	int		fd;
	int		len_list;
	char	*get_next;

	len_list = 0;
	get_next = NULL;
	splited_line = ft_split_except(line, ' ', 39, 34);
	if (!splited_line)
		return (NULL);
	if (!splited_line[1] || splited_line[0][2] != '\0')
		splited_line = without_space(line, 0, 0, splited_line);
	while (splited_line[len_list])
		len_list ++;
	fd = open("heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
		if (check_if_line_equal(fd, splited_line) == 1)
			break ;
	if (len_list == 2)
		return (tmp_fun_write_to_file(len_list, splited_line, fd, get_next));
	linee = change_the_line(splited_line, 0);
	free_list(splited_line, fd, 0, 0);
	return (linee);
}

// split the job and export data to pipex
int	split_jobs(char *line, char *path, t_main_struct *main_data)
{
	char	*res;

	if (line[0] == '<' && line[1] == '<')
	{
		if (check_if_ok(line, 2) == 1)
			return (1);
		else
		{
			res = write_to_file(line);
			if (res == NULL)
				return (1);
			export_data_to_pipex(res, path, main_data);
			unlink("heredoc.txt");
			free(res);
		}
	}
	else
		export_data_to_pipex(line, path, main_data);
	return (0);
}

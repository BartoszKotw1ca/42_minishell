/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:26:44 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/04 09:06:29 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// in this file we are checking if the line is equal to "<<" and if it is we are writing to file
// if not we are exporting data to pipex
// so we can say that we are spliting the jobs

//that function check if the line after << is empty
int	check_if_ok(char *line, int i)
{
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0')
	{
		printf("%s", "parse error near \'\\n\'\n");
		return (1);
	}
	return (0);
}

// free the list where is all line
void	free_list(char **splited_line, int fd, int i, int check)
{
	while (splited_line[i])
		free(splited_line[i++]);
	free(splited_line);
	splited_line = NULL;
	if (check == 0)
		close(fd);
}

// change the line to "< heredoc.txt" insted of << "something"
char	*change_the_line(char **splited_line, int i)
{
	char *line;

	free(splited_line[0]);
	splited_line[0] = malloc(2);
	if (!splited_line[0])
		return (NULL);
	splited_line[0][0] = '<';
	splited_line[0][1] = '\0';
	if (splited_line[1])
		free(splited_line[1]);
	splited_line[1] = ft_strdup("heredoc.txt");
	if (splited_line[1] == 0)
		return (NULL);
	while (splited_line[i])
		i ++;
	line = ft_listjoin(0, i, splited_line);
	return (line);
}

// check if the line is equal what is after << "something"
int	check_if_line_equal(int	fd, char **splited_line)
{
	char	*tmp;

	tmp = readline("heredoc>");
	if (ft_strncmp(tmp, splited_line[1], ft_strlen(tmp)) == 0)
	{
		free(tmp);
		return (1);
	}
	else
	{
		ft_putstr_fd(tmp, fd);
		ft_putstr_fd("\n", fd);
	}
	free(tmp);
	return (0);
}

char **without_space(char *line, int i, int j, char **splited_line)
{
	char	*li;
	int		len;

	len = ft_strlen(line);
	li = malloc(sizeof(char) * (len + 2));
	li[len + 1] = '\0';
	li[0] = '<';
	li[1] = '<';
	li[2] = ' ';
	i = 3;
	j = 2;
	while (line[j])
		li[i ++] = line[j ++];
	free_list(splited_line, 0, 0, 1);
	splited_line = ft_split_except(li, ' ', 39, 34);
	free(li);
	return (splited_line);
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
			break;
	if (len_list == 2)
	{
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
		return NULL;
	}
	linee = change_the_line(splited_line, 0);
	free_list(splited_line, fd, 0, 0);
	return (linee);
}

// split the job and export data to pipex
int	split_jobs(char *line, char *path)
{
	char *res;

	if (line[0] == '<' && line[1] == '<')
	{
		if (check_if_ok(line, 2) == 1)
			return (1);
		else
		{
			res = write_to_file(line);
			if (res == NULL)
				return (1);
			export_data_to_pipex(res, path);
			unlink("heredoc.txt");
			// free(res);
		}
		free(res);
	}
	else
		export_data_to_pipex(line, path);
	return (0);
}

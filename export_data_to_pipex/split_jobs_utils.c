/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_jobs_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:38:18 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/06 13:39:01 by bkotwica         ###   ########.fr       */
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

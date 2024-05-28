/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_lef_shif_oper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:26:44 by bkotwica          #+#    #+#             */
/*   Updated: 2024/05/28 19:57:22 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	for_two_shifts(char *line)
{
	int		i;
	char	**splited_line;
	char	*tmp;
	int		fd;

	i = 2;
	if (line[0] == '<' && line[1] == '<')
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == '\0')
		{
			printf("%s", "parse error near \'\\n\'");
			return (1);
		}
		else
		{
			splited_line = ft_split_except(line, ' ', 39);
			if (!splited_line)
				return (1);
			fd = open("heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
			while (1)
			{
				tmp = readline("heredoc>");
				if (ft_strncmp(tmp, splited_line[1], ft_strlen(splited_line[1])) == 0)
					break;
				else
				{
					ft_putstr_fd(tmp, fd);
					ft_putstr_fd("\n", fd);
				}
			}
			close(fd);
			// unlink("heredoc.txt");
		}
	}
	return (0);
}
int	main(void)
{
	char	*line;

	line = "<<   ' hello tak'";
	for_two_shifts(line);
	return (0);
}

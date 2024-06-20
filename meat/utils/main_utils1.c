/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:01:18 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/20 10:01:54 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_line(t_main_struct *main_data)
{
	main_data->line = ft_strtrim(main_data->tmp, " ");
	free(main_data->tmp);
	return (0);
}

char	*add_line_to_history(char *src, t_main_struct *main_data)
{
	char	*line;

	line = ft_strtrim(src, " ");
	free(src);
	if ((int)line[0] != 0 && same(main_data->history, line) == 0)
	{
		my_add_history(&main_data->history, ft_strdup(line));
		add_history(line);
	}
	return (line);
}

void	prepare_source(char *src, int i, int init)
{
	int	in_single;
	int	in_double;

	in_single = -1;
	in_double = -1;
	while (src[i])
	{
		if (src[i] == 34)
			in_double *= -1;
		if (src[i] == 39)
			in_single *= -1;
		if (src[i] == '|' && in_single == -1 && in_double == -1)
			init = 1;
		if (init == 1 && src[i] == '<')
		{
			src[i] = -5;
			if (src[i + 1] == '<')
				src[i + 1] = -6;
		}
		if (src[i] != ' ' && src[i] != '<' && src[i] != '|')
			init = 0;
		i++;
	}
}

void	finish_first_part(char **lines, int i, int j)
{
	char	*new_line;

	new_line = ft_calloc(sizeof(char), ft_strlen(lines[i]) + 7);
	j = ft_strlen(lines[i]);
	while (lines[i][j] != '|')
		j-- ;
	ft_memcpy(new_line, lines[i], ft_strlen(lines[i]));
	ft_memcpy(&new_line[j] + 1, " true", 5);
	free(lines[i]);
	lines[i] = new_line;
}

int	check_quotes(char *argv)
{
	int		i;
	int		doubl;
	int		one;

	i = -1;
	doubl = 0;
	one = 0;
	while (argv[++ i])
	{
		if (argv[i] == 39 && one == 0)
			one = 1;
		else if (argv[i] == 34 && doubl == 0)
			doubl = 1;
		else if (argv[i] == 39 && one == 1)
			one = 0;
		else if (argv[i] == 34 && doubl == 1)
			doubl = 0;
	}
	if (doubl == 0 && one == 0)
		return (0);
	return (1);
}

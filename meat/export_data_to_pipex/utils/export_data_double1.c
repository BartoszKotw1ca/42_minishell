/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_data_double1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:14:15 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/20 10:18:17 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_inside_red(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_com)
	{
		if (data->com[i].commend == NULL)
			return (1);
		i ++;
	}
	return (0);
}

void	count_pipes(t_data *data, char *argv)
{
	int		i;
	int		doubl;
	int		one;

	i = -1;
	doubl = 0;
	one = 0;
	data->pipes_counter = 1;
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
		else if (argv[i] == '|' && one == 0 && doubl == 0)
			data->pipes_counter += 1;
	}
}

int	check_line1(char *argv)
{
	int	i;

	i = strlen(argv) - 1;
	while (i >= 0 && argv[i] != '|')
	{
		if (argv[i] == '>' && i - 1 >= 0 && argv[i - 1] == '>')
			return (1);
		else if (argv[i] == '>' && skip_spaces_back(argv, i - 1) != '\0')
			return (2);
		else
			i--;
	}
	return (0);
}

void	free_splited_list(char **tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
		free(tmp[i ++]);
	free(tmp);
}

char	skip_spaces_back(char *str, int index)
{
	while (index >= 0 && str[index] == ' ')
		index--;
	if (index >= 0)
		return (str[index]);
	else
		return ('\0');
}

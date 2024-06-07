/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_data_infile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:02:57 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/07 15:18:01 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
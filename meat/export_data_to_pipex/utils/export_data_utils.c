/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_data_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:53:49 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/10 09:10:57 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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

char	skip_spaces(char *argv, int i)
{
	while (argv[i] && argv[i] == ' ')
		i ++;
	return (argv[i]);
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
	// (void) tmp;
	return (data);
}

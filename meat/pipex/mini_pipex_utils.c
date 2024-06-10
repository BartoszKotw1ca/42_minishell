/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:54:56 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/09 23:18:13 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	env_size(t_main_struct *main_data)
{
	int		size;
	t_list	*start;

	start = main_data->envr;
	size = 0;
	while(main_data->envr)
	{
		size += ft_strlen(main_data->envr->content) + 1;
		main_data->envr = main_data->envr->next;
	}
	main_data->envr = start;
	return (size);
}

char	*get_env_string(t_main_struct *main_data)
{
	char	*env_string;
	t_list	*start;
	char	*env_string_start;

	env_string = calloc(env_size(main_data) + 1, sizeof(char));
	start = main_data->envr;
	env_string_start = env_string;
	while(main_data->envr)
	{
		ft_strlcpy(env_string, main_data->envr->content, ft_strlen(main_data->envr->content) + 1);
		env_string += ft_strlen(main_data->envr->content);
		*env_string  = '\n';
		env_string ++;
		main_data->envr = main_data->envr->next;
		// printf("%s", env_string_start);
	}
	main_data->envr = start;
	return (env_string_start);
}

void	close_n_dup(int i, int (*fd)[2], int noc, t_data *data)
{
	int	ifd;
	int	ofd;

	if (i == -1 && data->infile && data->infile_ok == 0)
	{
		ifd = open(data->infile, O_RDONLY);
		dup2(ifd, 0);
		close(ifd);
	}
	if (i + 2 != noc)
		dup2(fd[i + 1][1], 1);
	else if (data->outfile)
	{
		ofd = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dup2(ofd, 1);
		close(ofd);
	}
	if (i > -1)
	{
		close(fd[i][1]);
		dup2(fd[i][0], 0);
		close(fd[i][0]);
	}
}

void	close_pipes(t_process *p, int i)
{
	close(p->pipes[i - 1][0]);
	close(p->pipes[i - 1][1]);
}

char	*read_var_name(char *src)
{
	char	*end;
	char	*var_name;
	int		i;

	i = 0;
	end = NULL;
	while (ft_isalnum(src[i]) != 0 || src[i] == '_')
		i++;
	end = &src[i];
	i = 0;
	var_name = calloc(end - src + 1, sizeof(char));
	while (&src[i] != end)
	{
		var_name[i] = src[i];
		i++;
	}
	if (*src == '?')
		var_name[0] = '?';
	return (var_name);
}

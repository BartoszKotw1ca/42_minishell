/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:54:56 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/20 09:39:29 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	env_size(t_main_struct *main_data)
{
	int		size;
	t_list	*start;

	start = main_data->envr;
	size = 0;
	while (main_data->envr)
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
	while (main_data->envr)
	{
		ft_strlcpy(env_string, main_data->envr->content,
			ft_strlen(main_data->envr->content) + 1);
		env_string += ft_strlen(main_data->envr->content);
		*env_string = '\n';
		env_string ++;
		main_data->envr = main_data->envr->next;
	}
	main_data->envr = start;
	return (env_string_start);
}

void	handle_input(int i, int (*fd)[2], t_data *data)
{
	int	ifd;

	if (i == 0 && data->com[i].infile)
	{
		ifd = open(data->com[i].infile, O_RDONLY);
		dup2(ifd, 0);
		close(ifd);
	}
	if (i > 0 && !data->com[i].infile)
	{
		close(fd[i - 1][1]);
		dup2(fd[i - 1][0], 0);
		close(fd[i - 1][0]);
	}
	else if (i > 0 && data->com[i].infile)
	{
		ifd = open(data->com[i].infile, O_RDONLY);
		close(fd[i - 1][0]);
		dup2(ifd, 0);
		close(ifd);
	}
}

void	handle_output(int i, int (*fd)[2], int noc, t_data *data)
{
	int	ofd;

	if (data->com[i].outfile)
	{
		if (i + 1 != noc)
			close(fd[i][1]);
		if (data->com[i].mode == 0)
			ofd = open(data->com[i].outfile,
					O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else
			ofd = open(data->com[i].outfile,
					O_CREAT | O_WRONLY | O_APPEND, 0777);
		dup2(ofd, 1);
		close(ofd);
	}
	else if (i + 1 != noc)
	{
		dup2(fd[i][1], 1);
		close(fd[i][1]);
	}
	else
		dup2(1, 1);
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

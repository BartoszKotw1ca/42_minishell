/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:21:32 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/19 21:47:11 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	same(t_list *history, char *line)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = history;
	while (tmp && tmp->next)
	{
		i ++;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (0);
	else if (ft_strncmp(tmp->content, line, ft_strlen(line)) == 0)
		return (1);
	return (0);
}

void	update_file(char *name, int content, t_main_struct *main_data)
{
	int		fd;
	char	*path;

	path = ft_strjoin(main_data->main_path, name);
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_putnbr_fd(content / 256, fd);
	close(fd);
	free(path);
}

char	*read_file(char *name, t_main_struct *main_data)
{
	char	*res;
	char	*path;
	int		fd;

	path = ft_strjoin(main_data->main_path, name);
	res = ft_calloc(5, sizeof(char));
	res[0] = -2;
	fd = open(path, O_RDONLY);
	read(fd, res + 1, 4);
	close(fd);
	free(path);
	return (res);
}

int	search_for(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

int	look_for_str(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	*to_find;

	if (!big && !len)
		return (0);
	if (!*little)
		return (0);
	to_find = (char *)little;
	str = (char *)big;
	i = 0;
	j = 0;
	if (*to_find == '\0')
		return (0);
	while (str[i] != 0 && len-- > 0)
	{
		while (str[i + j] == to_find[j] && str[i + j] != 0 && j < len + 1)
			j++;
		if (to_find[j] == 0)
			return (1);
		i++;
		j = 0;
	}
	return (0);
}

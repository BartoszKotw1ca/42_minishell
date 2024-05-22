/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:13:15 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/22 10:13:31 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	exit_error(char *message)
{
	perror(message);
	exit(1);
}

int	read_file(char *path, char **dest)
{
	int		fd;
	char	*temp;
	char	*result;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_error(path);
	result = "";
	temp = "a";
	while (temp)
	{
		temp = get_next_line(fd);
		if (temp && ft_strncmp(temp, ERROR_ALLOC, 13) == 0)
			exit_and_free(0, 2, "error while reading input file\n");
		if (temp)
		{
			result = ft_strjoin(result, temp);
			if (!result)
				exit_error("");
			free(temp);
		}
	}
	close(fd);
	*dest = result;
	return (0);
}

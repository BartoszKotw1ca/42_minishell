/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 21:08:46 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/11 16:28:13 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*alloc_error(int *mode)
{
	*mode = 1;
	return (ERROR_ALLOC);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	int			res;
	char		*line;
	static int	mode;

	if (mode == 0)
		string_tools(buffer, 1, 0);
	while (mode != 5 && BUFFER_SIZE != 0)
	{
		if (count_tools(buffer, 0, 0, BUFFER_SIZE) == 0)
		{
			string_tools(buffer, 1, 0);
			res = read(fd, buffer, BUFFER_SIZE);
			if (res == 0 || res == -1)
				return (check_last(line, &mode, res));
		}
		line = get_from_buffer(buffer, &mode);
		if (mode == 1)
		{
			mode = 3;
			return (line);
		}
	}
	return (NULL);
}

/* #include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*res;
	int		i;
	int		bs;

	if (argc > 0)
		fd = open(argv[1], O_RDONLY);
	res = "init";
	i = 0;
	bs = BUFFER_SIZE;
	printf("buffer size is: %d\n\n", bs);
	while (res && i < 14)
	{
		res = get_next_line(fd);
		if (res)
		{
			printf("%s", res);
			printf("--- --- ---\n");
		}
		i++;
		free(res);
	}
} */

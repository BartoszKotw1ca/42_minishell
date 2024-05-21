/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:33:08 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/11 18:25:58 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 0 strlen
// 1 strchr
int	count_tools(char *src, char c, int mode, int size)
{
	int	i;

	if (!src)
		return (0);
	i = 0;
	if (mode == 0)
	{
		while (src[i] && (i < size || size < 0))
			i++;
	}
	if (mode == 1)
	{
		while (src[i] && src[i] != c && (i < size || size < 0))
			i++;
	}
	if (i == size)
		i--;
	return (i);
}

// 0: moves bytes from start to the beginning of string, rest is set to zero 
// 1 bzero
char	*string_tools(char *src, int mode, int start)
{
	int		i;

	i = 0;
	if (mode == 0 && src)
	{
		while (start < BUFFER_SIZE)
		{
			src[i++] = src[start];
			start++;
		}
		while (i < BUFFER_SIZE)
			src[i++] = 0;
	}
	if (mode == 1)
	{
		while (i < BUFFER_SIZE)
			src[i++] = 0;
	}
	return (NULL);
}

// copies src to dest 
int	cut_copy_string(char *src, int start, char *dest, int size)
{
	int	i;

	if (!src || !dest)
		return (0);
	i = 0;
	while (src[i] && (size < 0 || i <= size))
		dest[start++] = src[i++];
	return (start);
}

// checks and returns last line if not null
char	*check_last(char *line, int *mode_4, int res)
{
	if (res == -1)
		return (ERROR_ALLOC);
	if (*mode_4 != 3 && *mode_4 != 0 && res != -1)
	{
		*mode_4 = 5;
		return (line);
	}
	else
		return (NULL);
}

// mode 1 - line is finished ready to return
// mode 2 - line is not finished
// mode 3 - line was returned and should be cleared
// mode 5 - last word was returned, no more work
char	*get_from_buffer(char *buffer, int *mode)
{
	static char	*t_line;
	static char	*temp;
	int			i;
	int			j;

	if (*mode == 3)
		t_line = NULL;
	temp = t_line;
	i = count_tools(buffer, '\n', 1, BUFFER_SIZE);
	j = count_tools(temp, 0, 0, -1);
	t_line = malloc(j + i + 2);
	if (!t_line)
		return (alloc_error(mode));
	cut_copy_string(temp, 0, t_line, -1);
	j = cut_copy_string(buffer, j, t_line, i);
	t_line[j] = 0;
	if (j > 0 && t_line[j - 1] == '\n')
		*mode = 1;
	else
		*mode = 2;
	string_tools(buffer, 0, i + 1);
	free(temp);
	return (t_line);
}

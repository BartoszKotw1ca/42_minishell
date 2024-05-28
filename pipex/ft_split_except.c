/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_except.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:44:36 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/28 17:21:29 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	count_items(char const *s, char c, char e)
{
	int		mode;
	size_t	count;
	int		in_e;

	mode = 0;
	count = 0;
	in_e = -1;
	while (*s)
	{
		if (*s != c && mode == 0 && in_e == -1)
		{
			mode = 1;
			count++;
		}
		else if (*s == c && in_e == -1)
			mode = 0;
		else if (*s == e)
			in_e *= -1;
		s++;
	}
	return (count);
}

static int	malloc_string(size_t i, char **result, size_t len, char const *s)
{
	size_t	a;

	s -= len;
	result[i] = (char *)malloc(len * sizeof(char) + 1);
	if (!result[i])
	{
		a = 0;
		while (a != i)
		{
			free(result[a]);
			a++;
		}
		return (1);
	}
	ft_strlcpy(result[i], s, len + 1);
	return (0);
}

static int	add_words(char **result, char const *s, char c, char e)
{
	size_t	i;
	size_t	len;
	int		in_e;

	i = 0;
	len = 0;
	in_e = -1;
	while (*s && *s == c)
		s++;
	while (1)
	{
		if (*s == e)
			in_e *= -1;
		if ((*s != c && *s) || (in_e == 1 && *s))
			len++;
		else if (len != 0)
		{
			if (malloc_string(i++, result, len, s) == 1)
				return (1);
			len = 0;
		}
		if (!*s)
			return (0);
		s++;
	}
}

void	clean_up_res(char **result, char e)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (result[i])
	{
		while (result[i][j])
		{
			if (result[i][j] == e && result[i][j + 1] != 0)
				ft_memmove(result[i], result[i] + 1, ft_strlen(result[i]));
			else if (result[i][j] == e)
				result[i][j] = 0;
			j++;
		}
		i++;
		j = 0;
	}
}

char	**ft_split_except(char const *s, char c, char e)
{
	char	**result;
	size_t	items;

	if (!s)
		return (NULL);
	items = count_items(s, c, e);
	result = (char **)malloc((items + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[items] = NULL;
	if (items == 0)
	{
		*result = NULL;
		return (result);
	}
	if (add_words(result, s, c, e) == 1)
	{
		free(result);
		return (NULL);
	}
	clean_up_res(result, e);
	return (result);
}

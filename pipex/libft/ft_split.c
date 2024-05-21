/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:44:36 by jponieck          #+#    #+#             */
/*   Updated: 2024/01/28 12:47:24 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_items(char const *s, char c)
{
	int		mode;
	size_t	count;

	mode = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && mode == 0)
		{
			mode = 1;
			count++;
		}
		else if (*s == c)
			mode = 0;
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

static int	add_words(char **result, char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (*s && *s == c)
		s++;
	while (1)
	{
		if (*s != c && *s)
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

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	items;

	if (!s)
		return (NULL);
	items = count_items(s, c);
	result = (char **)malloc((items + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[items] = NULL;
	if (items == 0)
	{
		*result = NULL;
		return (result);
	}
	if (add_words(result, s, c) == 1)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:01:48 by jponieck          #+#    #+#             */
/*   Updated: 2024/03/12 11:01:51 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	move_index(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	return (i);
}

int	move_index_back(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = 0;
	while (ft_strchr(set, s1[i]) && i > 0)
	{
		i--;
		j++;
	}
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*trmd;
	const char	*s0;
	size_t		i;

	if (!s1 || !set)
		return (NULL);
	s1 += move_index(s1, set);
	i = ft_strlen(s1) - move_index_back(s1, set);
	s0 = s1 + i;
	if (ft_strlen(s0) == 0)
		return (ft_strdup(""));
	trmd = (char *)malloc(sizeof(char) * (i + 2));
	if (!trmd)
		return (NULL);
	i = 0;
	while (s1 != s0)
		trmd[i++] = *s1++;
	trmd[i++] = *s0;
	trmd[i] = 0;
	return (trmd);
}

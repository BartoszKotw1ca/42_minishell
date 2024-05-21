/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:59:59 by jponieck          #+#    #+#             */
/*   Updated: 2024/03/12 11:00:01 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	joined = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
		return (NULL);
	while (*s1)
	{
		*joined++ = *s1++;
		i++;
	}
	while (*s2)
	{
		*joined++ = *s2++;
		i++;
	}
	*joined = 0;
	return (joined - i);
}

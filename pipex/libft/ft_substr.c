/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:02:00 by jponieck          #+#    #+#             */
/*   Updated: 2024/03/12 11:02:03 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;

	if (!s)
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	while (i < start)
	{
		s++;
		i++;
	}
	if (ft_strlen(s) > len)
		sub = (char *)malloc(len + 1);
	else
		sub = (char *)malloc(ft_strlen(s) + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s, len + 1);
	return (sub);
}

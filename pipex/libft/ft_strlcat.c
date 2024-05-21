/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:00:10 by jponieck          #+#    #+#             */
/*   Updated: 2024/03/12 11:00:12 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	rv;

	if (!dst && size == 0)
		return (ft_strlen(src));
	j = ft_strlen(dst);
	i = 0;
	if (ft_strlen(dst) <= size)
		rv = ft_strlen(src) + ft_strlen(dst);
	else
		rv = size + ft_strlen(src);
	if (size == 0)
		return (rv);
	while (src[i] && j < size - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (rv);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:54:14 by jponieck          #+#    #+#             */
/*   Updated: 2024/03/12 10:54:17 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*ft_s;
	size_t		i;

	ft_s = s;
	i = 0;
	while (i < n)
	{
		if (ft_s[i] == (char)c)
			return ((void *)(ft_s + i));
		i++;
	}
	return (NULL);
}

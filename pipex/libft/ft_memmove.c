/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:55:05 by jponieck          #+#    #+#             */
/*   Updated: 2024/03/12 10:55:07 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	m;
	size_t	i;

	i = 0;
	if (!src && !dest)
		return (NULL);
	if (src + n > dest && dest > src && n > 0)
	{
		i += (n -1);
		m = -1;
	}
	else
		m = 1;
	while (n > 0)
	{
		((char *)dest)[i] = ((char *)src)[i];
		if (n != 1)
			i += 1 * m;
		n--;
	}
	return (dest);
}

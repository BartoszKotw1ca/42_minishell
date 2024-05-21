/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:01:20 by jponieck          #+#    #+#             */
/*   Updated: 2024/03/12 11:01:24 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*test_strings(const char *big, const char *small, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (big[i])
	{
		k = i;
		while ((big[k] == small[j] && big[k]) || small[j] == '\0')
		{
			if (small[j] == '\0')
				return ((char *)&big[i]);
			j++;
			if (k == n)
				return (NULL);
			k++;
		}
		if (i == n)
			return (NULL);
		i++;
		j = 0;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *small, size_t n)
{
	if (!big && n == 0)
		return (NULL);
	if (ft_strlen(big) == 0 && ft_strlen(small) == 0)
		return ((char *)big);
	return (test_strings(big, small, n));
}

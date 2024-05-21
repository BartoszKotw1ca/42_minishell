/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:27:53 by jponieck          #+#    #+#             */
/*   Updated: 2024/03/12 10:45:05 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_z(const char *nptr)
{
	int	z;

	z = 0;
	while (nptr[z] && (nptr[z] >= 48 && nptr[z] <= 57))
		z++;
	return (z - 1);
}

int	ft_atoi(const char *nptr)
{
	int		d;
	int		z;
	int		i;
	int		n;

	n = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (nptr[0] == '-' || nptr[0] == '+')
	{
		n = 44 - nptr[0];
		nptr++;
	}
	d = 1;
	i = 0;
	z = find_z(nptr);
	while (z >= 0)
	{
		i += ((nptr[z] - 48) * d) * n;
		d *= 10;
		z--;
	}
	return (i);
}

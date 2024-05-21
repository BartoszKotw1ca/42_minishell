/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:51:05 by jponieck          #+#    #+#             */
/*   Updated: 2024/03/12 10:51:09 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_power(int n, int p)
{
	int	base;

	if (p == 0)
		return (1);
	base = n;
	while (p > 1)
	{
		n = n * base;
		p--;
	}
	return (n);
}

static int	count_digits(int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
		i++;
	while (n >= 1 || n <= -1)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	get_digit(int n, char *res, int j, int len)
{
	int	i;
	int	sign;

	if (n < 0)
		sign = -1;
	else
		sign = 1;
	if (n < to_power(10, len) && n > -to_power(10, len))
	{
		res[j] = '0';
		return (0);
	}
	i = 1;
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		i *= 10;
	}
	res[j] = n * sign + 48;
	return (n * i);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		j;
	int		len;

	j = 0;
	len = count_digits(n);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	if (n < 0)
	{
		*res = '-';
		len--;
		j++;
	}
	while (len-- > 0)
		n -= get_digit(n, res, j++, len);
	res[j] = 0;
	return (res);
}

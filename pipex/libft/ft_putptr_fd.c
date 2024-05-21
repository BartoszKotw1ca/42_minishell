/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:28:53 by jponieck          #+#    #+#             */
/*   Updated: 2024/04/16 11:58:25 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	conv_to_16(unsigned long n, char *base, int fd, int *chars)
{
	if (n == 0)
		return ;
	else
	{
		conv_to_16(n / 16, base, fd, chars);
		(*chars)++;
	}
	ft_putchar_fd(base[n % 16], fd);
}

int	ft_putptr_fd(void *p, int fd)
{
	unsigned long	n;
	char			*base;
	int				chars;

	chars = 0;
	if (!p)
	{
		ft_putstr_fd("(nil)", fd);
		return (5);
	}
	base = "0123456789abcdef";
	n = (unsigned long)p;
	ft_putstr_fd("0x", fd);
	chars += 2;
	conv_to_16(n, base, fd, &chars);
	return (chars);
}

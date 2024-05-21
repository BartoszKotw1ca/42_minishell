/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:28:53 by jponieck          #+#    #+#             */
/*   Updated: 2024/04/16 11:57:50 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	conv_to_16(unsigned int n, char *base, int fd, int *chars)
{
	if (n == 0)
		return ;
	else
	{
		(*chars)++;
		conv_to_16(n / 16, base, fd, chars);
	}
	ft_putchar_fd(base[n % 16], fd);
}

int	ft_puthex_fd(unsigned int n, int fd, char cse)
{
	int		chars;
	char	*base;

	chars = 0;
	if (n == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	if (cse == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	conv_to_16(n, base, fd, &chars);
	return (chars);
}

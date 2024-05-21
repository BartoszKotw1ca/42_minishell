/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:57:26 by jponieck          #+#    #+#             */
/*   Updated: 2024/03/12 10:57:30 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_number(long int nb, int fd)
{
	char	c;

	if (nb < 10)
	{
		c = nb + 48;
		write(fd, &c, 1);
	}
	else
	{
		write_number(nb / 10, fd);
		write_number(nb % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	write_number(nb, fd);
}

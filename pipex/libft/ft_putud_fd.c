/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putud_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:28:53 by jponieck          #+#    #+#             */
/*   Updated: 2024/04/16 11:58:54 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_ud(unsigned int nb, int fd)
{
	char	c;

	if (nb < 10)
	{
		c = nb + 48;
		write(fd, &c, 1);
	}
	else
	{
		write_ud(nb / 10, fd);
		write_ud(nb % 10, fd);
	}
}

int	ft_putud_fd(unsigned int nb, int fd)
{
	int	chars;

	write_ud(nb, fd);
	if (nb == 0)
		return (1);
	chars = 0;
	while (nb != 0)
	{
		nb = nb / 10;
		chars++;
	}
	return (chars);
}

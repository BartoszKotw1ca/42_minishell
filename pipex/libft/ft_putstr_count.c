/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:28:53 by jponieck          #+#    #+#             */
/*   Updated: 2024/04/16 11:58:35 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_count(char *v, int fd)
{
	if (!v)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	ft_putstr_fd(v, fd);
	return (ft_strlen(v));
}

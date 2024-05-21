/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:28:53 by jponieck          #+#    #+#             */
/*   Updated: 2024/04/16 11:57:00 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *src, ...)
{
	int		chars;
	va_list	ap;

	va_start(ap, src);
	chars = print_stuff(src, ap);
	va_end(ap);
	return (chars);
}

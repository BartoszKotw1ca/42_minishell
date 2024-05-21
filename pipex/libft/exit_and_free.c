/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:01:45 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/11 18:31:42 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	exit_and_free(int args, int code, char *message, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, message);
	ft_putstr_fd(message, code);
	while (i < args)
	{
		free(va_arg(ap, void *));
		i++;
	}
	va_end(ap);
	exit(code);
}

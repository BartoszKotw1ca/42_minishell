/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:53:48 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/04 07:46:08 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_gnl_list
{
	char			*str_buf;
	struct s_gnl_list	*next;
}					g_list;

g_list	*find_last_node(g_list *list);
int		is_newline(g_list *list);
int		len_to_newline(g_list *list);
void	dealloc(g_list **list, g_list *clean_node, char *buffer);
void	polish_list(g_list **list);
void	copy_str(g_list *list, char *str);
void	append(g_list **list, char *buffer);
void	create_list(g_list **list, int fd);
char	*get_line(g_list *list);
char	*get_next_line(int fd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:07:37 by nshahid           #+#    #+#             */
/*   Updated: 2024/05/11 17:02:10 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

# ifndef ERROR_ALLOC
#  define ERROR_ALLOC "_ERROR_ALLOC_"
# endif

# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	free_split(char **res);
int		ft_isascii(int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putnbr_fd(int n, int fd);
char	*ft_strnstr(const char *big, const char *small, size_t n);
int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *s);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t	ft_strlen(const char *s);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_toupper(int c);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_isalpha(int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_isalnum(int c);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_isprint(int c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_tolower(int c);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putchar_fd(char c, int fd);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_printf(const char *src, ...);
int		count_args(const char *src);
int		print_stuff(const char *s, va_list ap);
int		ft_putptr_fd(void *p, int fd);
int		ft_putud_fd(unsigned int n, int fd);
int		ft_puthex_fd(unsigned int n, int fd, char cse);
int		ft_putnbr_count(int v, int fd);
int		ft_putstr_count(char *v, int fd);
int		ft_putchar_fd_count(char c, int fd);
char	*get_next_line(int fd);
int		count_tools(char *src, char c, int mode, int size);
char	*string_tools(char *src, int mode, int start);
int		cut_copy_string(char *src, int start, char *dest, int size);
char	*check_last(char *line, int *mode_4, int res);
char	*get_from_buffer(char *buffer, int *mode);
char	*alloc_error(int *mode);
int		read_file(char *path, char **dest);
void	exit_and_free(int args, int code, char *message, ...);

#endif

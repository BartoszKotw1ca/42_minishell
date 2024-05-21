CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = libft.a

SRC_FILES = exit_and_free.c read_file.c free_split.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_striteri.c ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c ft_strjoin.c ft_substr.c ft_calloc.c ft_strlcpy.c ft_strdup.c ft_memcmp.c ft_memchr.c ft_memmove.c ft_strlen.c ft_bzero.c ft_memset.c ft_memcpy.c ft_memccpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_atoi.c ft_strncmp.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_printf.c ft_putchar_fd_count.c ft_puthex_fd.c ft_putnbr_count.c ft_putptr_fd.c ft_putstr_count.c ft_putud_fd.c print_stuff.c get_next_line.c get_next_line_utils.c
SRC_FILES_BONUS = ft_lstmap.c ft_lstiter.c ft_lstclear.c ft_lstdelone.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_FILES_BONUS = $(SRC_FILES_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rcs $(NAME) $(OBJ_FILES)

bonus: $(OBJ_FILES) $(OBJ_FILES_BONUS)
	ar rcs $(NAME) $(OBJ_FILES) $(OBJ_FILES_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJ_FILES) $(OBJ_FILES_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

rebonus: fclean bonus


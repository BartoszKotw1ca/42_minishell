CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# CFLAGS = -g
NAME = pipex

SRC_FILES = pipex.c utils.c
OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): libft/libft.a $(OBJ_FILES)
	$(CC) $(SRC_FILES) -I. -I./libft -L. -L./libft -lft -o $(NAME)

libft/libft.a:
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	make clean -C libft
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

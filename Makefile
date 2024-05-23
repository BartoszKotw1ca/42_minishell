FLAGS = -Wall -Wextra -Werror -g
NAME = minishell
LIB = ./mylibft/mylibft.a
SRC = main.c
OBJDIR = Obj/
OBJ := $(SRC:%.c=$(OBJDIR)%.o)

all: $(NAME)
	@echo "Compilation completed."

$(NAME): mylibft/mylibft.a $(OBJ)
	@cc $(FLAGS) -lreadline $^ -o $@ $(LIB)

$(OBJDIR)%.o: %.c
	@mkdir -p $(@D)
	@cc $(FLAGS) -c $< -o $@

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

mylibft/mylibft.a:
	@make -s -C mylibft

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@make -s -C mylibft fclean
	@rm -rf $(OBJDIR)
	@echo "Cleared."

re: fclean all

.PHONY: all, clean, fclean, re

# there was a problem with
# read_file and i add this 	temp = "a";
# we should change it
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -g
# NAME = minishell
# LIBFT = pipex/libft/libft.a
# SRC_FILES = main.c
# OBJ_FILES = $(SRC_FILES:.c=.o)

# all: $(NAME)

# $(NAME): $(LIBFT) $(OBJ_FILES)
# 	$(CC) $(CFLAGS) -lreadline -o $(NAME) $(SRC_FILES) -Lpipex/libft -lft

# $(LIBFT):
# 	make -C pipex/libft

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean: 
# 	make clean -C pipex/libft
# 	rm -f $(OBJ_FILES)

# fclean: clean
# 	rm -f $(NAME)
# 	make fclean -C pipex/libft

# re: fclean all

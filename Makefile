# FLAGS = -Wall -Wextra -Werror -g
FLAGS = -g
NAME = minishell
LIB = ./mylibft/mylibft.a
# SRC = main.c export_data_to_pipex.c ft_listjoin.c
SRC = pipex/export_data_to_pipex.c \
		pipex/ft_listjoin.c \
		pipex/mini_pipex.c \
		pipex/mp_utils.c \
		pipex/check_commands.c \
		main.c

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

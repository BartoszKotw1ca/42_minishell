# FLAGS = -Wall -Wextra -Werror -g
FLAGS = -g
NAME = minishell
LIB = ./mylibft/mylibft.a
# SRC = main.c export_data_to_pipex.c ft_listjoin.c
SRC = pipex/export_data_to_pipex.c \
		pipex/ft_listjoin.c \
		pipex/mini_pipex.c \
		pipex/mp_utils.c \
		history/history.c \
		pipex/check_commands.c \
		pipex/ft_split_except.c \
		pipex/split_jobs.c \
		handle_env.c \
		main.c

OBJDIR = Obj/
OBJ := $(SRC:%.c=$(OBJDIR)%.o)

all: $(NAME)
	@echo "Compilation completed."

$(NAME): mylibft/mylibft.a $(OBJ)
	@cc $(FLAGS) -L/readline -I/readline  $^ -o $@ $(LIB) -lreadline

$(OBJDIR)%.o: %.c
	@mkdir -p $(@D)
	@cc $(FLAGS) -c -L/readline -I/readline -lreadline $< -o $@

%.o: %.c
	@cc $(FLAGS) -c -L/readline -I/readline -lreadline $< -o $@

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

# FLAGS = -Wall -Wextra -Werror -g
FLAGS = -g
NAME = minishell
LIB = ./mylibft/mylibft.a
# SRC = main.c export_data_to_pipex.c ft_listjoin.c
SRC =	export_data_to_pipex/export_data_to_pipex.c \
		export_data_to_pipex/split_jobs.c \
		export_data_to_pipex/split_jobs_utils.c \
		pipex/mini_pipex.c \
		pipex/check_commands.c \
		utils/ft_listjoin.c \
		utils/ft_split_except.c \
		utils/mp_utils.c \
		history/history.c \
		pipex/handle_env.c \
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

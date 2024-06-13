FLAGS = -Wall -Wextra -Werror -g
# FLAGS = -g
NAME = minishell
LIB = ./mylibft/mylibft.a
SRC =	meat/export_data_to_pipex/export_data_to_pipex.c \
		meat/export_data_to_pipex/split_jobs.c \
		meat/export_data_to_pipex/utils/split_jobs_utils.c \
		meat/export_data_to_pipex/utils/export_data_utils.c \
		meat/export_data_to_pipex/utils/export_data_outfile.c \
		meat/export_data_to_pipex/utils/export_data_infile.c \
		meat/pipex/mini_pipex.c \
		meat/pipex/check_commands.c \
		meat/pipex/handle_env.c \
		meat/pipex/mini_pipex_utils.c \
		meat/pipex/mini_pipex_utils_2.c \
		meat/utils/ft_listjoin.c \
		meat/utils/ft_split_except.c \
		meat/utils/main_utils.c \
		meat/utils/mp_utils.c \
		meat/utils/ft_split_except_test.c \
		meat/change_dir/change_dir.c \
		meat/history/history.c \
		meat/signals/signals.c \
		meat/export_and_unset/export_and_unset.c \
		main.c

OBJDIR = Obj/
OBJ := $(SRC:%.c=$(OBJDIR)%.o)

all: $(NAME)

$(NAME): mylibft/mylibft.a $(OBJ)
	@cc $(FLAGS) $^ -o $@ $(LIB) -lreadline

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

# FLAGS = -Wall -Wextra -Werror -g
# # FLAGS = -g
# NAME = minishell
# LIB = ./mylibft/mylibft.a
# # SRC = main.c export_data_to_pipex.c ft_listjoin.c
# SRC =	meat/export_data_to_pipex/export_data_to_pipex.c \
# 		meat/export_data_to_pipex/split_jobs.c \
# 		meat/export_data_to_pipex/utils/split_jobs_utils.c \
# 		meat/export_data_to_pipex/utils/export_data_utils.c \
# 		meat/export_data_to_pipex/utils/export_data_outfile.c \
# 		meat/export_data_to_pipex/utils/export_data_infile.c \
# 		meat/pipex/mini_pipex.c \
# 		meat/pipex/check_commands.c \
# 		meat/pipex/handle_env.c \
# 		meat/pipex/mini_pipex_utils.c \
# 		meat/utils/ft_listjoin.c \
# 		meat/utils/ft_split_except.c \
# 		meat/utils/main_utils.c \
# 		meat/utils/mp_utils.c \
# 		meat/change_dir/change_dir.c \
# 		meat/history/history.c \
# 		meat/signals/signals.c \
# 		main.c

# OBJDIR = Obj/
# OBJ := $(SRC:%.c=$(OBJDIR)%.o)

# all: $(NAME)
# 	@echo "Compilation completed."

# $(NAME): mylibft/mylibft.a $(OBJ)
# 	@cc $(FLAGS) $^ -o $@ $(LIB) -lreadline

# $(OBJDIR)%.o: %.c
# 	@mkdir -p $(@D)
# 	@cc $(FLAGS) -c $< -o $@

# %.o: %.c
# 	@cc $(FLAGS) -c $< -o $@

# mylibft/mylibft.a:
# 	@make -s -C mylibft

# clean:
# 	@rm -f $(OBJ)
# 	@rm -rf $(OBJDIR)

# fclean: clean
# 	@rm -f $(NAME)
# 	@make -s -C mylibft fclean
# 	@rm -rf $(OBJDIR)
# 	@echo "Cleared."

# re: fclean all

# .PHONY: all, clean, fclean, re

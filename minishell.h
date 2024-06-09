/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:50:39 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/09 22:37:22 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mylibft/mylibft.h"

# include "readline/readline.h"
# include "readline/history.h"
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <unistd.h>

typedef struct s_data
{
	char	*infile;
	char	*outfile;
	char	**commends;
	int		start;
	int		end;
	int		num_of_com;
	char	**paths;
	int		mode;
	int		ex_stat;
	int		infile_ok;
	t_list	*envr;
	char	**tmp;
}			t_data;

typedef struct s_process
{
	char	**args;
	char	*path;
	int		*pid;
	int		(*pipes)[2];
}	t_process;

typedef struct s_split_data
{
	char	*src;
	char	*new;
	char	c;
	char	e;
	char	f;
	int		in_ef;
}	t_split_data;

typedef struct s_main_struct
{
	char				*line;
	char				*path;
	char				*tmp;
	t_list				*history;
	t_list				*envr;
	char				**envp;
	int					i;
	char				**ted;
	struct sigaction	sa;
}				t_main_struct;

// export_data_to_pipex.c
void	export_data_to_pipex(char *argv, char *path, t_main_struct *main_data);

// ft_listajoin.c
char	*ft_listjoin(int start, int end, char **lista);

// history.c
void	my_add_history(t_list **lista, char *str);
void	del_node(void *content);
void	print_history(t_list *lista);

// check_commands.c
char	*find_path(char *command, t_data *data, int i);
void	check_commands(t_process *p, t_data *data, t_main_struct *main_data);

// mp_utils.c
void	free_split(char **res);
void	print_error(char *mes1, char *mes2);

// main_utils.c
void	update_file(char *name, int content);
char	*read_file(char *name);

// ft_split_except.c
char	**ft_split_except(char *s, char c, char e, char f);

// handle_env.c
void	set_env(t_main_struct *main_data, char **envp);
char	*read_env(t_main_struct *main_data, char *key);
void	print_env(t_main_struct *main_data);
void	export_env(t_main_struct *main_data, char *key_val);
void	unset_env(t_main_struct *main_data, char *key_val);

// split_jobs.c
char	*tmp_fun_write_to_file(int len_list,
			char **splited_line, int fd, char *get_next);
char	*write_to_file(char *line);
int		split_jobs(char *line, char *path, t_main_struct *main_data);

// split_jobs_utils.c
int		check_if_ok(char *line, int i);
void	free_list(char **splited_line, int fd, int i, int check);
char	*change_the_line(char **splited_line, int i);
int		check_if_line_equal(int fd, char **splited_line);
char	**without_space(char *line, int i, int j, char **splited_line);

// signals.c
void	ctr_c_sig_handler(int sig);
void	signal_prepare(t_main_struct *main_data);

// utils.c
int		look_for_str(const char *big, const char *little, size_t len);
int		search_for(char *line, char c);
int		same(t_list *history, char *line);

// change_dir.c
void	change_directory(char *line, char *path, t_main_struct *main_data);

// export_data_utils.c
char	*write_to(char *str, int len);
void	count_commnads(t_data *data);
void	free_dataa(t_data *data, char **tmp);
char	skip_spaces(char *argv, int i);
t_data	*data_for_null(t_data *data, char **tmp);

// export_data_outfile.c
int		check_if_zero(int *i, t_data *data, int j, char **tmp);
void	write_to_outfile(char **tmp, t_data *data, int i, int j);
void	process_data(char **tmp, t_data *data, int j);
char	*change_line(t_data *data, char *argv, int check);
void	in_the_middle(char	**tmp, t_data *data, int i, int j);

// export_data_infile.c
void	write_to_infile(char **tmp, t_data *data);
int		check_the_line(char *argv, t_data *data);
void	check_infile(t_data *data);

// mini_pipex_utils.c
void	close_n_dup(int i, int (*fd)[2], int noc, t_data *data);
void	close_pipes(t_process *p, int i);
char	*read_var_name(char *src);
char	*get_env_string(t_main_struct *main_data);

// mini_pipex.c
void	mini_pipex(t_data *data, t_main_struct *main_data);

// export_and_unset.c
void	check_inside_export(t_main_struct *main_data, int j);
void	check_for_export(t_main_struct *main_data);
void	initialize_export(t_main_struct *main_data);
void	initialize_unset(t_main_struct *main_data);

#endif

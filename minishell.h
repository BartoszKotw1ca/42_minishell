/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:50:39 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/06 19:11:02 by jponieck         ###   ########.fr       */
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
	char	*line;
	char	*path;
	char	*tmp;
	t_list	*history;
	struct	sigaction sa;
	t_list	*envr;
	char	**envp;
}				t_main_struct;

// export_data_to_pipex.c
void	export_data_to_pipex(char *argv, char *path, t_main_struct *main_data);

// ft_listajoin.c
char	*ft_listjoin(int start, int end, char **lista);

void	mini_pipex(t_data *data, t_main_struct *main_data);
void	get_paths(t_data *data, char **envp);
void	my_add_history();
void	del_node(void *content);
void	print_history(t_list *lista);
char	*find_path(char *command, t_data *data, int i);
void	free_split(char **res);
void	check_commands(t_process *p, t_data *data);
void	print_error(char *mes1, char *mes2);
char	**ft_split_except(char *s, char c, char e, char f);
int		split_jobs(char *line, char *path, t_main_struct *main_data);
void	update_file(char *name, int content);
char	*read_file(char *name);
void	set_env(t_main_struct *main_data, char **envp);
char	*read_env(t_main_struct *main_data, char *key);
void	free_dataa(t_data *data, char **tmp);

// split_jobs.c
char	*tmp_fun_write_to_file(int len_list, char **splited_line, int fd, char *get_next);
char	*write_to_file(char *line);
int		split_jobs(char *line, char *path, t_main_struct *main_data);

// split_jobs_utils.c
int		check_if_ok(char *line, int i);
void	free_list(char **splited_line, int fd, int i, int check);
char	*change_the_line(char **splited_line, int i);
int		check_if_line_equal(int fd, char **splited_line);
char	**without_space(char *line, int i, int j, char **splited_line);

#endif

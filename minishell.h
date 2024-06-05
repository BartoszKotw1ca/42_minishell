/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:50:39 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/05 14:12:02 by bkotwica         ###   ########.fr       */
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

// export_data_to_pipex.c
void	export_data_to_pipex(char *argv, char *path);

// ft_listajoin.c
char	*ft_listjoin(int start, int end, char **lista);

void	mini_pipex(t_data *data);
void	get_paths(t_data *data, char **envp);
void	my_add_history();
void	del_node(void *content);
void	print_history(t_list *lista);
char	*find_path(char *command, t_data *data, int i);
void	free_split(char **res);
void	check_commands(t_process *p, t_data *data);
void	print_error(char *mes1, char *mes2);
char	**ft_split_except(char *s, char c, char e, char f);
int		split_jobs(char *line, char *path);
void	update_file(char *name, int content);
char	*read_file(char *name);

#endif

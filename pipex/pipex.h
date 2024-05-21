/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:19:47 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/20 22:09:49 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "sys/wait.h"

typedef struct s_vars
{
	char	**command_1;
	char	**command_2;
	char	*prog_1;
	char	*prog_2;
	int		in_file;
	int		out_file;
	int		p_fd[2];
	char	**paths;
}	t_vars;

void	clean_up(t_vars *vars, char *message, int is_error);
void	test_args(int argc, t_vars *vars);
char	*find_path(char **program, t_vars *vars);
void	print_error(char *mes1, char *mes2, char *mes3, int perr);

#endif
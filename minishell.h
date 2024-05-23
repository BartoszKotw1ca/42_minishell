/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:50:39 by bkotwica          #+#    #+#             */
/*   Updated: 2024/05/23 16:15:53 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// #include "mylibft/mylibft.h"
# include "pipex/libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

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
}			t_data;

// export_data_to_pipex.c
t_data	export_data_to_pipex(char *argv);

// ft_listajoin.c
char	*ft_listjoin(int start, int end, char **lista);

#endif

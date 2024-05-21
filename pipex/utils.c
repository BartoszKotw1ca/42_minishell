/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:56:44 by jponieck          #+#    #+#             */
/*   Updated: 2024/05/20 22:10:10 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **program, t_vars *vars)
{
	int		i;
	char	*curr_path;
	char	*prog_path;

	if (!program)
		return (NULL);
	prog_path = ft_strjoin("/", program[0]);
	if (!prog_path)
		return (NULL);
	i = 0;
	while (vars->paths[i])
	{
		curr_path = ft_strjoin(vars->paths[i], prog_path);
		if (!curr_path)
			return (NULL);
		if (access(curr_path, F_OK) == 0)
		{
			free(prog_path);
			return (curr_path);
		}
		free(curr_path);
		i++;
	}
	free(prog_path);
	return ("no_prog");
}

void	test_args(int argc, t_vars *vars)
{
	if (argc != 5)
	{
		ft_putstr_fd("pipex: invalid number of arguments\n", 2);
		clean_up(vars, NULL, 1);
	}
	if (!vars->command_1 || !vars->command_2 || !vars->paths)
	{
		ft_putstr_fd("pipex: allocation error\n", 2);
		clean_up(vars, NULL, 1);
	}
}

void	print_error(char *mes1, char *mes2, char *mes3, int perr)
{
	ft_putstr_fd(mes1, 2);
	ft_putstr_fd(mes2, 2);
	ft_putstr_fd(mes3, 2);
	if (perr == 1)
		perror("");
	else
		ft_putstr_fd("\n", 2);
}

void	clean_up(t_vars *vars, char *message, int is_error)
{
	if (message)
		perror(message);
	if (vars->command_1)
		free_split(vars->command_1);
	if (vars->command_2)
		free_split(vars->command_2);
	if (vars->paths)
		free_split(vars->paths);
	if (vars->prog_1 && ft_strncmp("no_prog", vars->prog_1, 7) != 0)
		free(vars->prog_1);
	if (vars->prog_2 && ft_strncmp("no_prog", vars->prog_2, 7) != 0)
		free(vars->prog_2);
	if (is_error != 0)
		exit (is_error);
}

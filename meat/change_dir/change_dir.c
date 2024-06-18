/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponieck <jponieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:25:06 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/18 20:22:12 by jponieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_directory(char *line, t_main_struct *main_data)
{
	char	**tmp;
	int		i;
	int		res;

	i = 0;
	tmp = ft_split_except(line, ' ', 39, 34);
	if (ft_strncmp(line, "cd", ft_strlen(line)) == 0 && !tmp[1])
		res = chdir(getenv("HOME"));
	else if (look_for_str(line, "..", ft_strlen(line)) && !tmp[2])
		res = chdir("..");
	else if (search_for(line, '|') == 1)
	{
		split_jobs(line, main_data);
		return ;
	}
	else
		res = chdir(tmp[1]);
	if (res == -1)
		printf("cd: %s: No such file or directory\n", tmp[1]);
	while (tmp[i])
		free(tmp[i ++]);
	free(tmp);
}

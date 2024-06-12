/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_except_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:01:24 by bkotwica          #+#    #+#             */
/*   Updated: 2024/06/12 15:00:07 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void prepare_str(t_split_data *sd, int i)
{
    char quote = 0;
    while (*sd->src)
    {
        if (*sd->src == sd->e || *sd->src == sd->f)
        {
            if (quote == 0)
                quote = *sd->src;
            else if (quote == *sd->src)
                quote = 0;
        }
        if (*sd->src == sd->c && quote == 0)
            sd->new[i] = -5;
        else
            sd->new[i] = *sd->src;
        sd->src++;
        i++;
    }
}

void back_to_origin(char **splited, int i, int j)
{
    while (splited[i])
    {
        while (splited[i][j])
        {
            if (splited[i][j] == -5)
                splited[i][j] = ' ';
            j++;
        }
        j = 0;
        i++;
    }
}

char **split_ex(char *src, char c, char e, char f)
{
    char *src_new;
    char **splited;
    t_split_data sd;

    sd.src = src;
    sd.new = ft_calloc(ft_strlen(src) + 1, sizeof(char));
    sd.c = c;
    sd.e = e;
    sd.f = f;
    sd.in_ef = 0;
    prepare_str(&sd, 0);
    splited = ft_split(sd.new, -5);
    back_to_origin(splited, 0, 0);
    free(sd.new);
    return splited;
}

// int main(void)
// {
//     char **result;
//     char *str = "echo \"co to jest | to jest to\" | druga komenda";

//     result = split_ex(str, '|', '\'', '\"');

//     // Print the result
//     for (int i = 0; result[i] != NULL; i++)
//     {
//         printf("%s\n", result[i]);
//     }

//     // Free the result
//     for (int i = 0; result[i] != NULL; i++)
//     {
//         free(result[i]);
//     }
//     free(result);

//     return 0;
// }


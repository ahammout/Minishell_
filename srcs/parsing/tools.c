/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:46 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/01 18:25:55 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int generate_error(t_data *data)
{
    exitS = 2;
    ft_putstr_fd(data->err, 2);
    ft_putstr_fd("\n", 2);
    return (0);
}

/// Exit Minishell 
void    exit_minishell(t_data *data, char *err, int exit_option)
{
    if (exit_option == 0)
        free_env_list(data);
    else if (exit_option == 1)
    {
        free_env_list(data);
        free(data->buffer);
        free_tokens_list(data);
    }
    else if (exit_option == 2)
    {
        if (data->err)
            free(data->err);
        free_env_list(data);
        free_tokens_list(data);
        free_cmds_list(data);
    }
    if (err)
    {
        ft_putstr_fd(err, 2);
        exit(EXIT_FAILURE);
    }
    exit (exitS);
}

int white_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isprint(str[i]))
            return (1);
        i++;
    }
    return (0);
}

void    display_table(char **dstr)
{
    int i;

    i = 0;
    while (dstr[i])
    {
        printf ("Line[ %d ]: %s\n",i, dstr[i]);
        i++;
    }
}

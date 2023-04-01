/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:46 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/01 00:15:38 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_t_exec(t_exec *exec)
{
    int i = 0;
    if (exec)
    {
        if (exec->str)
        {
            while (exec->str[i])
            {
                free(exec->str[i]);
                i++;
            }
            free(exec->str);
        }
        free(exec);
    }
}

void    free_data(t_data *data)
{
    // if (data->buffer)
    //     free(data->buffer);
    // if (data->path)
    //     free(data->path);
    free_env_list(data);
    free_t_exec(data->cmds);
    free_tokens_list(data);
}

int generate_error(t_data *data)
{
    exitS = 2;
    ft_putstr_fd(data->err, 2);
    ft_putstr_fd("\n", 2);
    return (0);
}

void    exit_error(t_data *data, char *err)
{
    free(data->buffer);
    free_tokens_list(data);
    ft_putstr_fd(err, 2);
    exit(EXIT_FAILURE);
}

char    **ft_2strdup(char **tab1)
{
    int len;
    int i;
    char    **tab2;

    len = 0;
    i = 0;
    while(tab1[len])
        len++;
    tab2 = malloc(sizeof(char*) * len);
    while (tab1[i])
    {
        tab2[i] = ft_strdup(tab1[i]);
        i++;
    }
    tab2[i] = NULL;
    return (tab2);
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

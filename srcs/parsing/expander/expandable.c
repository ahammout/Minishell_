/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:13:06 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/06 00:27:31 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void var_not_exist(t_data *data, char *lexem, char *pids)
{
    t_ref   ref;
    int     size;

    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    size = update_size(lexem, pids, NULL, NULL);
    if (size > 1)
    {
        data->tokens->lex = ft_calloc(size, sizeof(char));
        while (pids[ref.j + 1])
            data->tokens->lex[ref.l++] = pids[ref.j++];
        if (lexem[ref.i] == '@' || lexem[ref.i] == '*' || ft_isdigit(lexem[ref.i]))
        {
            ref.i++;
            while (lexem[ref.i])
                data->tokens->lex[ref.l++] = lexem[ref.i++];
            data->tokens->lex[ref.l] = '\0';
        }
        data->tokens->type = KEYWORD;
    }
    else
    {
        data->tokens->lex = NULL;
        data->tokens->type = EMPTY;
    }
}

void    exit_status(t_data *data, char *lexem, char *pids)
{
    t_ref   ref;
    int     size;
    char    *e_status;
    int     e;

    ref.i = 1;
    ref.j = 0;
    ref.l = 0;
    e = 0;
    e_status = ft_itoa(g_exit_status);
    size = update_size(lexem, pids, NULL, e_status);
    if (size)
    {
        data->tokens->lex = ft_calloc(size, sizeof(char));
        while (pids[ref.j + 1])
            data->tokens->lex[ref.l++] = pids[ref.j++];
        while (e_status[e])
            data->tokens->lex[ref.l++] = e_status[e++];
        while (lexem[ref.i])
            data->tokens->lex[ref.l++] = lexem[ref.i++];
        data->tokens->lex[ref.l] = '\0';
        data->tokens->type = KEYWORD;
    }
    free(e_status);
}

void    var_exist(t_data *data, char *pids, char *value)
{
    t_ref   ref;
    int     size;

    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    size = update_size(NULL, pids, value, NULL);
    if (size > 1)
    {
        data->tokens->lex = ft_calloc(size, sizeof(char));
        while (pids[ref.j + 1])
            data->tokens->lex[ref.l++] = pids[ref.j++];
        while (value[ref.i])
            data->tokens->lex[ref.l++] = value[ref.i++];
        data->tokens->lex[ref.l] = '\0';
        data->tokens->type = KEYWORD;
    }
}

void    expandable(t_data *data, char *lexem, char *pids)
{
    char    *value;
    int     i;

    i = 0;
    while (lexem[i] == EXPAND_)
        i++;
    value = get_value(data, get_var(data, lexem + i));
    if (value)
        var_exist(data, pids, value);
    else if (lexem[i] == '?')
        exit_status(data, lexem + i, pids);
    else
        var_not_exist(data, lexem + i, pids);
    if (value)
        free(value);
}
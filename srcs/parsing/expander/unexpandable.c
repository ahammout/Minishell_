/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpandable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:12:56 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/03 16:46:21 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int update_size_(char *lexem, char *pids)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (lexem[i] == EXPAND_)
        i++;
    while (lexem[i] && lexem[i] != EXPAND_)
    {
        len++;
        i++;
    }
    i = 0;
    while (pids[i])
    {
        if (pids[i] != '$')
            len++;
        i++;
    }
    return (len + 1);
}

void    non_param (t_data *data, char *lexem, char *pids)
{
    t_ref   ref;

    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    data->tokens->lex = ft_calloc((update_size_(lexem, pids) + 1), sizeof(char));
    while (lexem[ref.i] == EXPAND_)
        ref.i++;
    while (pids[ref.j])
    {
        if (pids[ref.j] == '$' \
        && (ft_isdigit(lexem[ref.i]) || lexem[ref.i] == '@'))
            break;
        data->tokens->lex[ref.l++] = pids[ref.j++];
    }
    data->tokens->lex[ref.l] = '\0';
    data->tokens->type = KEYWORD;
}

void    unexpandable(t_data *data, char *lexem, char *pids)
{
    t_ref   ref;

    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    data->tokens->lex = ft_calloc(update_size_(lexem, pids), sizeof (char));
    while (lexem[ref.i] == EXPAND_)
        ref.i++;
    while (pids[ref.j])
    {
        if (pids[ref.j] != '$')
        {
            data->tokens->lex[ref.l] = pids[ref.j];
            ref.l++;
        }
        ref.j++;
    }
    while (lexem[ref.i])
        data->tokens->lex[ref.l++] = lexem[ref.i++];
    data->tokens->lex[ref.l] = '\0';
    data->tokens->type = KEYWORD;
}


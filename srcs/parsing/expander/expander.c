/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:13:17 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/31 23:01:43 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int handle_dolar_sign(char *lexem, char **pids)
{
    char    *pid;
    int     i;

    i = 0;
    pid = ft_itoa(getppid());
    (*pids) = ft_strdup("");
    while (lexem[i] == EXPAND_)
    {
        if (lexem[i] == EXPAND_ && lexem[i + 1] == EXPAND_)
        {
            (*pids) = ft_strjoin((*pids), pid);
            i += 2;
        }
        else
        {
            (*pids) = ft_strjoin((*pids), "$");
            i++;
        }
    }
    return (i);
}

char    *free_old_lex(t_data *data)
{
    char    *lex_tmp;

    lex_tmp = ft_strdup(data->tokens->lex);
    free(data->tokens->lex);
    data->tokens->lex = NULL;
    return (lex_tmp);
}

void    expand_handler(t_data *data)
{
    char    *lexem;
    char    *pids;
    int     index;

    lexem = free_old_lex(data);
    index = handle_dolar_sign(lexem, &pids);
    if ((index % 2) && lexem[index])
        expandable(data, lexem, pids);
    else if (!(index % 2) && lexem[index])
        unexpandable(data, lexem, pids);
    else
        non_param(data, lexem, pids);
    free (lexem);
    free(pids);
}

t_tokens    *expander(t_data *data)
{
    t_tokens    *head;

    head = data->tokens;
    while (data->tokens != NULL)
    {
        if (data->tokens->type == EXPAND_ && data->tokens->prev->type != HEREDOC)
            expand_handler(data);
        data->tokens = data->tokens->next;
    }
    data->tokens = head;
    return (head);
}
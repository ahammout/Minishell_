/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:13:17 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/03 03:36:53 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*handle_dolar_sign(char *lexem, int	*index)
{
    char    *pids;
    char    *p;
    int     fst_alloc;
    int     i;

    i = 0;
    fst_alloc = 1;
    p = ft_itoa(getppid());
    while (lexem[i] == EXPAND_)
    {
        if (lexem[i] == EXPAND_ && lexem[i + 1] == EXPAND_)
        {
            if (fst_alloc)
            {
                pids = ft_strdup(p);
                fst_alloc = 0;
            }
            else
			    pids = ft_strjoin(pids, p);
			i += 2;
        }
        else
        {
            if (fst_alloc)
            {
                pids = ft_strdup("$");
                fst_alloc = 0;
            }
            else
                pids = ft_strjoin(pids, "$");
            i++;
        }
    }
	*index = i;
    free(p);
    return (pids);
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
    pids = handle_dolar_sign(lexem, &index);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:45:24 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/08 03:38:31 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int q_keyword(t_data *data, char *lexem)
{
    t_ref ref;

    ref.l = 0;
    ref.i = 0;
    ref.j = 0;
    while (lexem[ref.l] && lexem[ref.l] != EXPAND_)
        ref.l++;
    if (ref.l)
    {
        data->tokens->lex = malloc(sizeof(char) * ref.l + 1);
        if (!data->tokens->lex)
            exit_minishell(data, "Minishell: Allocation failed.");
        while (lexem[ref.i] && lexem[ref.i] != EXPAND_)
            data->tokens->lex[ref.j++] = lexem[ref.i++];
        data->tokens->lex[ref.j] = '\0';
        if (is_quoted(lexem[ref.i]) || lexem[ref.i] == EXPAND_)
            data->tokens->attach = 1;
        data->tokens->type = KEYWORD;
    }
    return (ref.i);
}

void split_token(t_data *data)
{
    t_tokens *head;
    t_tokens *next;
    t_ref    ref;
    char     *lexem;

    head = data->tokens;
    next = data->tokens->next;
    lexem = ft_strdup(data->tokens->lex);
    free(data->tokens->lex);
    data->tokens->lex = NULL;
    ref.i = 0;
    ref.l = 0;
    while (lexem[ref.i])
    {
        create_new_node(data, &ref.l);
        if (head->attach && next)
            data->tokens->attach = 1;
        if (lexem[ref.i] == EXPAND_)
            ref.i += expand(data, lexem + ref.i);
        else if (lexem[ref.i] && lexem[ref.i] != EXPAND_)
            ref.i += q_keyword(data, lexem + ref.i);
        data->tokens->next = next;
    }
    data->tokens = head;
    free(lexem);
}
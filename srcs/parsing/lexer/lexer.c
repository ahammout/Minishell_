/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:13:35 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/08 03:13:14 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int special_op(t_data *data, char *lexem, int type)
{
    t_ref   ref;

    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    while (lexem[ref.l] == type)
        ref.l++;
    data->tokens->lenght = ref.l;
    data->tokens->lex = malloc(sizeof(char) * (ref.l + 1));
    if (!data->tokens->lex)
        exit_minishell(data, "Minishell: Allocation failed.");
    while (lexem[ref.i] == type)
        data->tokens->lex[ref.j++] = lexem[ref.i++];
    data->tokens->lex[ref.j] = '\0';
    optype(data, type);
    return (ref.i);
}

int keyword(t_data *data, char *lexem)
{
    t_ref   ref;

    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    while (lexem[ref.l] && is_keyword(lexem[ref.l]))
        ref.l++;
    data->tokens->lenght = ref.l;
    data->tokens->lex = malloc(sizeof(char) * (ref.l + 1));
    if (!data->tokens->lex)
        exit_minishell(data, "Minishell: Allocation failed.");
    while (lexem[ref.i] && is_keyword(lexem[ref.i]))
        data->tokens->lex[ref.j++] = lexem[ref.i++];
    data->tokens->lex[ref.j] = '\0';
    if (is_quoted(lexem[ref.i]) || lexem[ref.i] == EXPAND_)
        data->tokens->attach = 1;
    data->tokens->type = KEYWORD;
    return (ref.i);
}

int expand(t_data *data, char *lexem)
{
    t_ref   ref;

    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    while (lexem[ref.l] == EXPAND_ || lexem[ref.l] == '@' || lexem[ref.l] == '*')
        ref.l++;
    while (ft_isalpha(lexem[ref.l]) || ft_isdigit(lexem[ref.l]) \
        || lexem[ref.l] == '_' || lexem[ref.l] == '?')
        ref.l++;
    data->tokens->lex = malloc(sizeof(char) * (ref.l + 1));
    if (!data->tokens->lex)
        exit_minishell(data, "Minishell: Allocation failed.");
    while (lexem[ref.i] == EXPAND_ || lexem[ref.i] == '@' \
        || lexem[ref.i] == '*')
        data->tokens->lex[ref.j++] = lexem[ref.i++];
    while (ft_isalpha(lexem[ref.i]) || ft_isdigit(lexem[ref.i]) \
        || lexem[ref.i] == '_' || lexem[ref.i] == '?')
        data->tokens->lex[ref.j++] = lexem[ref.i++];
    data->tokens->lex[ref.j] = '\0';
    if (is_quoted(lexem[ref.i]) || lexem[ref.i] == EXPAND_ || is_keyword(lexem[ref.i]))
        data->tokens->attach = 1;
    data->tokens->type = EXPAND_;
    return (ref.i);
}

int quotes(t_data *data, char *lexem, char type)
{
    t_ref   ref;
    int     quote;

    quote = 0;
    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    while (lexem[ref.l])
    {
        if (lexem[ref.l] == type)
            quote++;
        ref.l++;
        if (quote == 2)
            break;
    }
    data->tokens->lex = malloc(sizeof(char) * (ref.l + 1));
    if (!data->tokens->lex)
        exit_minishell(data, "Minishell: Allocation failed.");
    quote = 0;
    while (lexem[ref.i])
    {
        if (lexem[ref.i] == type)
            quote++;
        data->tokens->lex[ref.j++] = lexem[ref.i++];
        if (quote == 2)
            break;
    }
    data->tokens->lex[ref.j] = '\0';
    if (is_quoted(lexem[ref.i]) || lexem[ref.i] == EXPAND_ || is_keyword(lexem[ref.i]))
        data->tokens->attach = 1;
    data->tokens->type = type;
    return (ref.i);
}

t_tokens *lexer(t_data *data)
{
    t_tokens    *head;
    int         add_node;
    int         i;
    
    head = NULL;
    if (white_check (data->buffer))
    {
        i = 0;
        add_node = 0;
        init_tokens_list(data);
        head = data->tokens;
        while (data->buffer[i] && white_check (data->buffer + i))
        {
            create_new_node(data, &add_node);
            while (is_whitespace(data->buffer[i]))
                i++;
            if (is_quoted(data->buffer[i]))
                i += quotes(data, data->buffer + i, data->buffer[i]);
            else if (data->buffer[i] == EXPAND_)
                i += expand(data, data->buffer + i);
            else if (is_keyword(data->buffer[i]))
                i += keyword(data, data->buffer + i);
            else if (is_special_op(data->buffer[i]))
                i += special_op(data, data->buffer + i, data->buffer[i]);
        }
    }
    free(data->buffer);
    data->tokens = head;
    return (head);
}
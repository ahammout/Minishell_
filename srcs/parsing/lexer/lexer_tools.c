/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:13:51 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/03 04:23:48 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    init_tokens_list(t_data *data)
{
    data->heredoc = 0;
    data->tokens = malloc(sizeof(t_tokens));
    if (!data->tokens)
        exit_minishell(data, "Minishell: Allocation failed.", 1);
    data->tokens->attach = 0;
    data->tokens->next = NULL;
    data->tokens->prev = data->tokens;
}

void    add_new_node(t_data *data)
{
    t_tokens *node;

    node = malloc(sizeof(t_tokens));
    if (!node)
        exit_minishell(data, "Malloc: Allocation failed.", 1);
    node->next = NULL;
    node->attach = 0;
    node->prev = data->tokens;
    data->tokens->next = node;
}

void    create_new_node(t_data *data, int *add_node)
{
    if (*add_node)
    {
        add_new_node(data);
        data->tokens = data->tokens->next;
    }
    else
        *add_node = 1;
}

void    display_tokens(t_tokens *token)
{
    t_tokens    *head;
    int         n;

    head = token;
    n = 0;
    while (head != NULL)
    {
        printf("---- Node %d ----\n", n);
        printf("Lexeme: %s\n",head->lex);
        printf("Type: %d\n\n", head->type);
        printf("Countinu: %d\n", head->attach);
        // printf("---- Previous Node ----\n");
        // printf("Lexeme: %s\n", head->prev->lex);
        // printf("Type: %d\n\n", head->prev->type);
        n++;
        head = head->next;
    }
}
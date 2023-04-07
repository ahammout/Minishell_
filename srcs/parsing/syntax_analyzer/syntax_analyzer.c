/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:12:24 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/06 22:26:58 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    analyze_redirections(t_data *data)
{
    t_tokens    *token;

    if (!data->err)
    {
        if (data->tokens->type == REDOUT || data->tokens->type == APPEND \
            || data->tokens->type == REDIN || data->tokens->type == HEREDOC)
        {
            token = data->tokens;
            if (token->lenght > 2)
                data->err = ft_strdup("Minishell: syntax error near unexpected token `newline'");
            token = token->next;
            if (!token && !data->err)
                data->err = ft_strdup("Minishell: syntax error near unexpected token `newline'");
            analyze_end (data, token);
        }
    }
}

void    analyze_pipe(t_data *data)
{    
    if (data->tokens->type == PIPE && !data->err)
    {
        if (data->tokens->lenght > 1 || data->tokens->next == NULL)
            data->err = ft_strjoin("Minishell: syntax error near unexpected token `", "|'");
    }
}

void    analyze_begin_end (t_data *data)
{
    t_tokens    *token;

    token = data->tokens;
    analyze_begin(data, token);
    if (token->next && !data->err)
    {
        while (token->next && !is_metecharacter(token->type))
            token = token->next;
        if (token->next == NULL)
            analyze_end(data, token);
    }
}

t_tokens    *syntax_analyzer (t_data *data)
{
    t_tokens    *head;

    head = data->tokens;
    analyze_begin_end(data);
    while (data->tokens != NULL && !data->err)
    {
        analyze_quotes(data);
        analyze_pipe(data);
        analyze_redirections(data);
        data->tokens  = data->tokens->next;
    }
    data->tokens = head;
    if (data->err && !data->heredoc)
        return (generate_error(data), (void *)0);
    return (head);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:36:39 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/02 03:18:21 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//// STOP IN THE LAST WANTED TOKEN

char    *attach_arguments(t_data *data)
{
    char    *arg;

    arg = ft_strdup("");
    while (data->tokens->attach)
    {
        if (data->tokens->type != EMPTY)
            arg = ft_strjoin(arg, data->tokens->lex);
        data->tokens = data->tokens->next;
    }
    if (data->tokens->lex && data->tokens->type != EMPTY)
        arg = ft_strjoin(arg, data->tokens->lex);
    return (arg);
}

int get_size(t_data *data)
{
    t_tokens    *tmp;
    int         size;

    tmp = data->tokens;
    size = 0;
    while (tmp && !is_redirection(tmp->type) && tmp->type != PIPE)
    {
        if (tmp->type != EMPTY)
            size++;
        tmp = tmp->next;
    }
    return (size);
}

char    **get_cmd_args(t_data *data)
{
    t_ref       ref;
    char        **str;

    ref.i = 0;
    str = malloc(sizeof(char *) * (get_size(data) + 1));
    if (!str)
        exit_minishell(data, "Minishell: Allocation failed.", 2);
    while (data->tokens && !is_redirection(data->tokens->type) \
        && data->tokens->type != PIPE)
    {
        if (data->tokens->type != EMPTY)
        {
            if (data->tokens->attach)
                str[ref.i] = attach_arguments(data);
            else
                str[ref.i] = ft_strdup(data->tokens->lex);
            ref.i++;
        }
        data->tokens = data->tokens->next;
    }
    str[ref.i] = NULL;
    return (str);
}

t_exec  *tokens_to_cmds(t_data *data)
{
    t_exec      *head;
    t_tokens    *ptr;

    init_cmds_list(data);
    head = data->cmds;
    ptr = data->tokens;
    while (data->tokens)
    {
        if (data->tokens && data->tokens->type == KEYWORD)
            data->cmds->str = get_cmd_args(data);
        if (data->tokens && !redirections_handler(data))
        {
            data->tokens = ptr;
            data->cmds = head;
            return (free_data(data));
        }
        if (data->tokens && data->tokens->type == PIPE)
            next_cmd(data);
    }
    data->cmds = head;
    free_tokens_list(data);
    // display_cmds(data->cmds);
    return (head);
}

////////////////////////////////// PARSE_LINE //////////////////////////////

t_exec  *parser(t_data *data)
{
    if (lexer(data))
    {
        if (syntax_analyzer(data))
        {
            if (expander(data))
            {
                display_tokens(data->tokens);
                // exit(0);
                return (tokens_to_cmds(data));
            }
        }
    }
    return (0);
}
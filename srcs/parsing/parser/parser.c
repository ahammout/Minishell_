/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:36:39 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/30 22:22:12 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int get_size(t_data *data)
{
    t_tokens    *ptr;
    int         size;

    ptr = data->tokens;
    size = 0;
    while (data->tokens && !is_redirection(data->tokens->type) && data->tokens->type != PIPE)
    {
        if (data->tokens->type != EMPTY)
            size++;
        data->tokens = data->tokens->next;
    }
    data->tokens = ptr;
    return (size);
}

char    **get_cmd_args(t_data *data)
{
    t_ref   ref;
    char    **str;

    ref.i = 0;
    str = malloc(sizeof(char *) * (get_size(data) + 1));
    if (!str)
        exit_error(data, "Minishell: Allocation failed.");
    while (data->tokens && !is_redirection(data->tokens->type) && data->tokens->type != PIPE)
    {
        if (data->tokens->type != EMPTY)
        {
            str[ref.i] = ft_strdup(data->tokens->lex);
            ref.i++;
        }
        data->tokens = data->tokens->next;
    }
    str[ref.i] = NULL;
    return (str);
}

t_exec  *parser(t_data *data)
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
        if (!redirection_handler(data))
        {
            data->tokens = ptr;
            return (head);
        }
        if (data->tokens && data->tokens->type == PIPE)
            next_cmd(data);
    }
    data->tokens = ptr;
    data->cmds = head;
    //// OPTIONAL FUNCTION CALL
    // display_cmds(data->cmds);
    return (head);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:09:59 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/30 22:01:57 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int append_handler(t_data *data)
{
    if (data->tokens->type == APPEND)
        data->tokens = data->tokens->next;
    data->cmds->out_file = open(data->tokens->lex, O_WRONLY | O_APPEND);
    if (data->cmds->out_file == -1 && data->tokens->type != APPEND)
        data->cmds->out_file = open(data->tokens->lex, O_CREAT | O_WRONLY | O_APPEND, 0777);
    data->tokens = data->tokens->next;
    if (data->tokens && (data->tokens->type == KEYWORD || data->tokens->type == REDOUT))
    {
        close(data->cmds->out_file);
        append_handler(data);
    }
    return (1);
}

int redout_handler(t_data *data)
{
    if (data->tokens->type == REDOUT)
        data->tokens = data->tokens->next;
    data->cmds->out_file = open(data->tokens->lex, O_WRONLY);
    if (data->cmds->out_file != -1 && data->tokens->type != REDOUT)
    {
        close(data->cmds->out_file);
        unlink(data->tokens->lex);
        data->cmds->out_file = open(data->tokens->lex, O_WRONLY | O_CREAT, 0777);
    }
    if (data->cmds->out_file == -1 && data->tokens->type != REDOUT)
        data->cmds->out_file = open(data->tokens->lex, O_WRONLY | O_CREAT, 0777);
    data->tokens = data->tokens->next;
    if (data->tokens && (data->tokens->type == KEYWORD || data->tokens->type == REDOUT))
    {
        close(data->cmds->out_file);
        redout_handler(data);
    }
    return (1);
}

int redin_handler(t_data *data)
{
    
    if (data->tokens && data->tokens->type == REDIN)
        data->tokens = data->tokens->next;
    data->cmds->in_file = open(data->tokens->lex, O_RDONLY );
    if (data->cmds->in_file == -1)
    {
        data->err = 1;
        printf("Minishell: %s: No such file or directory\n", data->tokens->lex);
        return (0);
    }
    data->tokens = data->tokens->next;
    if (data->tokens && (data->tokens->type == KEYWORD || data->tokens->type == REDIN))
    {
        close(data->cmds->in_file);
        redin_handler(data);
    }
    if (data->err)
        return (0);
    return (1);
}

int redirection_handler(t_data *data)
{
    while (data->tokens && data->tokens->type != PIPE)
    {
        if (data->tokens && data->tokens->type == REDOUT)
            redout_handler(data);
        else if (data->tokens && data->tokens->type == APPEND)
            append_handler (data);
        else if (data->tokens && data->tokens->type == REDIN)
        {
            if (!redin_handler(data))
                return (0);
        }
        else if (data->tokens->type == HEREDOC)
        {
            if (!heredoc_handler(data))
                return (0);
        }
        else
            data->cmds = data->cmds->next;
    }
    return (1);
}
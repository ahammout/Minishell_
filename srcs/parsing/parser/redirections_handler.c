/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:09:59 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/04 01:26:06 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char    *no_such_file(char *file_name)
{
    char    *error;

    error = ft_strjoin("Minshell: ", file_name);
    error = ft_strjoin_free1(error, ": No such file or directory");
    return (error);
}

void    append_handler(t_data *data)
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
}

void    redout_handler(t_data *data)
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
}

int redin_handler(t_data *data)
{
    if (data->tokens && data->tokens->type == REDIN)
        data->tokens = data->tokens->next;
    data->cmds->in_file = open(data->tokens->lex, O_RDONLY);
    if (data->cmds->in_file == -1)
    {
        data->err = no_such_file(data->tokens->lex);
        return (generate_error(data), 0);
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

int redirections_handler(t_data *data)
{    
    if (data->tokens && is_redirection(data->tokens->type))
    {
        while (data->tokens && data->tokens->type != PIPE)
        {
            if (data->tokens && data->tokens->type == REDOUT)
                redout_handler(data);
            else if (data->tokens && data->tokens->type == APPEND)
                append_handler(data);
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
        }
    }
    // exit (0);
    return (1);
}
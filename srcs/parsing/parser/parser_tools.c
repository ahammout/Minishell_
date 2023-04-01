/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:59:47 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/01 18:48:14 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int is_redirection(int type)
{
    if (type == REDIN || type == REDOUT || type == APPEND || type == HEREDOC)
        return (1);
    return (0);
}

void init_cmds_list(t_data *data)
{
    data->cmds = malloc(sizeof(t_exec));
    if (!data->cmds)
        exit_minishell(data, "Minishell: Allocation failed", 2);
    data->cmds->in_file = 0;
    data->cmds->out_file = 1;
    data->cmds->next = NULL;
}

void next_cmd(t_data *data)
{
    t_exec *node;

    node = malloc(sizeof(t_exec));
    if (!node)
        exit_minishell(data, "Minishell: Allocation failed", 2);
    node->in_file = 0;
    node->out_file = 1;
    node->next = NULL;
    data->cmds->next = node;
    data->cmds = data->cmds->next;
    data->tokens = data->tokens->next;
}

void    display_cmds(t_exec *cmds)
{
    t_exec *head;
    int     n;
    int     i;

    head = cmds;
    n = 0;
    while (cmds != NULL)
    {
        i = 0;
        printf ("-------------- CMD %d -----------------\n\n", n++);
        while (cmds->str[i])
        {
            printf("  + Str [ %d ]: %s\n", i, cmds->str[i]);
            i++;
        }
        printf("\n");
        printf("* Input FD: %d\n", cmds->in_file);
        printf("* Output FD: %d\n\n", cmds->out_file);
        cmds = cmds->next;
    }
    cmds = head;
}
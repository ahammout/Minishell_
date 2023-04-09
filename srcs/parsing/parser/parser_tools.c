/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:15:56 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 00:18:49 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_size(t_data *data)
{
	t_tokens	*tmp;
	int			size;

	size = 0;
	if (data->tokens)
	{
		tmp = data->tokens;
		while (tmp && !is_redirection(tmp->type) && tmp->type != PIPE)
		{
			if (tmp->type != EMPTY)
			{
				if (tmp->attach)
				{
					while (tmp->attach)
						tmp = tmp->next;
				}
				size++;
			}
			tmp = tmp->next;
		}
	}
	return (size);
}

int	is_redirection(int type)
{
	if (type == REDIN || type == REDOUT || type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

void	init_cmds_list(t_data *data)
{
	data->cmds = malloc(sizeof(t_exec));
	if (!data->cmds)
		exit_minishell(data, "Minishell: Allocation failed");
	data->cmds->str = NULL;
	data->cmds->cmd_status = NULL;
	data->cmds->in_file = 0;
	data->cmds->out_file = 1;
	data->cmds->next = NULL;
}

void	next_cmd(t_data *data)
{
	t_exec	*node;

	node = malloc(sizeof(t_exec));
	if (!node)
		exit_minishell(data, "Minishell: Allocation failed");
	node->str = NULL;
	node->cmd_status = NULL;
	node->in_file = 0;
	node->out_file = 1;
	node->next = NULL;
	data->cmds->next = node;
	data->cmds = data->cmds->next;
	data->tokens = data->tokens->next;
}

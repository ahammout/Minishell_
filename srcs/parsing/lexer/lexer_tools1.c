/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:26:53 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 03:43:52 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	init_tokens_list(t_data *data)
{
	data->heredoc = 0;
	data->tokens = malloc(sizeof(t_tokens));
	if (!data->tokens)
		exit_minishell(data, "Minishell: Allocation failed.");
	data->tokens->attach = 0;
	data->tokens->next = NULL;
	data->tokens->prev = data->tokens;
}

void	add_new_node(t_data *data)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (!node)
		exit_minishell(data, "Malloc: Allocation failed.");
	node->next = NULL;
	node->attach = 0;
	node->prev = data->tokens;
	data->tokens->next = node;
}

void	create_new_node(t_data *data, int *add_node)
{
	if (*add_node)
	{
		add_new_node(data);
		data->tokens = data->tokens->next;
	}
	else
		*add_node = 1;
}

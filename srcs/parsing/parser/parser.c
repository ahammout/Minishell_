/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:36:39 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/08 16:11:12 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *join_arguments(t_data *data)
{
	char *arg;

	arg = ft_strdup("");
	while (data->tokens->attach)
	{
		if (data->tokens->type != EMPTY)
			arg = ft_strjoin_free1(arg, data->tokens->lex);
		data->tokens = data->tokens->next;
	}
	if (data->tokens->lex && data->tokens->type != EMPTY)
		arg = ft_strjoin_free1(arg, data->tokens->lex);
	return (arg);
}

int get_size(t_data *data)
{
	t_tokens *tmp;
	int size;

	tmp = data->tokens;
	size = 0;
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
	return (size);
}

void    command_arguments_handler(t_data *data)
{
	t_ref   ref;
	char    **str;
	int     size; 

	ref.i = 0;
	str = NULL;
	size = get_size(data);
	if (size)
	{
		str = malloc(sizeof(char *) * (size + 1));
		if (!str)
			exit_minishell(data, "Minishell: Allocation failed.");
		while (data->tokens && data->tokens->type != PIPE)
		{
			if (data->tokens->type != EMPTY)
			{
				if (data->tokens->attach)
					str[ref.i] = join_arguments(data);
				else
					str[ref.i] = ft_strdup(data->tokens->lex);
				ref.i++;
			}
			data->tokens = data->tokens->next;
		}
		str[ref.i] = NULL;
	}
	else
	{
		while (data->tokens && data->tokens->type != PIPE)
			data->tokens = data->tokens->next;
	}
	data->cmds->str = str;
}

t_exec *tokens_to_cmds(t_data *data)
{
	t_exec *head;
	t_tokens *tmp;

	init_cmds_list(data);
	head = data->cmds;
	tmp = data->tokens;
	while (data->tokens)
	{
		if (!redirections_handler(data))
		{
			data->tokens = tmp;
			data->cmds = head;
			return (free_data(data), (void *)0);
		}
		command_arguments_handler(data);
		if (data->tokens && data->tokens->type == PIPE)
			next_cmd(data);
	}
	data->cmds = head;
	data->tokens = tmp;
	free_tokens_list(data);
	return (head);
}

////////////////////////////////// PARSE_LINE //////////////////////////////

t_exec *parser(t_data *data)
{
	if (lexer(data))
	{
		if (syntax_analyzer(data))
		{
			// display_tokens(data->tokens)
			if (expander(data))
			{
				return (tokens_to_cmds(data));
			}
		}
	}
	return (0);
}
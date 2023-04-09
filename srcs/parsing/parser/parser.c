/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:51:17 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 15:03:45 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*join_arguments(t_data *data)
{
	char	*arg;

	arg = ft_strdup("");
	while (data->tokens && data->tokens->attach)
	{
		if (data->tokens->type != EMPTY)
			arg = ft_strjoin_free1(arg, data->tokens->lex);
		data->tokens = data->tokens->next;
	}
	if (data->tokens->lex && data->tokens->type != EMPTY)
		arg = ft_strjoin_free1(arg, data->tokens->lex);
	return (arg);
}

char	**fill_str(t_data *data, int size)
{
	char	**str;
	int		i;

	i = 0;
	str = malloc(sizeof(char *) * (size + 1));
	if (!str)
		exit_minishell(data, "Minishell: Allocation failed.");
	while (data->tokens && data->tokens->type != PIPE)
	{
		if (data->tokens->type != EMPTY)
		{
			if (data->tokens->attach)
				str[i] = join_arguments(data);
			else
				str[i] = ft_strdup(data->tokens->lex);
			i++;
		}
		data->tokens = data->tokens->next;
	}
	str[i] = NULL;
	return (str);
}

void	command_arguments_handler(t_data *data)
{
	char	**str;
	int		size;

	str = NULL;
	size = get_size(data);
	if (size)
		str = fill_str(data, size);
	else
	{
		while (data->tokens && data->tokens->type != PIPE)
			data->tokens = data->tokens->next;
	}
	data->cmds->str = str;
}

t_exec	*tokens_to_cmds(t_data *data)
{
	t_tokens	*ptr;
	t_exec		*head;

	init_cmds_list(data);
	head = data->cmds;
	ptr = data->tokens;
	while (data->tokens)
	{
		if (!redirections_handler(data))
		{
			data->tokens = ptr;
			data->cmds = head;
			return (free_data(data), (void *)0);
		}
		command_arguments_handler(data);
		if (data->tokens && data->tokens->type == PIPE)
			next_cmd(data);
	}
	data->cmds = head;
	data->tokens = ptr;
	free_tokens_list(data);
	return (head);
}
////////////////////////////////// PARSE_LINE //////////////////////////////

t_exec	*parser(t_data *data)
{
	if (lexer(data))
	{
		if (syntax_analyzer(data))
		{
			if (expander(data))
				return (tokens_to_cmds(data));
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 03:31:28 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 15:00:55 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	special_op(t_data *data, char *lexem, int type)
{
	t_ref	ref;

	ref.i = 0;
	ref.j = 0;
	ref.l = 0;
	while (lexem[ref.l] == type)
		ref.l++;
	data->tokens->lenght = ref.l;
	data->tokens->lex = malloc(sizeof(char) * (ref.l + 1));
	if (!data->tokens->lex)
		exit_minishell(data, "Minishell: Allocation failed.");
	while (lexem[ref.i] == type)
		data->tokens->lex[ref.j++] = lexem[ref.i++];
	data->tokens->lex[ref.j] = '\0';
	optype(data, type);
	return (ref.i);
}

int	keyword(t_data *data, char *lexem)
{
	t_ref	ref;

	ref.i = 0;
	ref.j = 0;
	ref.l = 0;
	while (lexem[ref.l] && is_keyword(lexem[ref.l]))
		ref.l++;
	data->tokens->lenght = ref.l;
	data->tokens->lex = malloc(sizeof(char) * (ref.l + 1));
	if (!data->tokens->lex)
		exit_minishell(data, "Minishell: Allocation failed.");
	while (lexem[ref.i] && is_keyword(lexem[ref.i]))
		data->tokens->lex[ref.j++] = lexem[ref.i++];
	data->tokens->lex[ref.j] = '\0';
	if (is_quoted(lexem[ref.i]) || lexem[ref.i] == EXPAND_)
		data->tokens->attach = 1;
	data->tokens->type = KEYWORD;
	return (ref.i);
}

void	tokenize_line(t_data *data)
{
	int	i;
	int	add_node;

	i = 0;
	add_node = 0;
	while (data->line[i] && white_check(data->line + i))
	{
		create_new_node(data, &add_node);
		while (is_whitespace(data->line[i]))
			i++;
		if (is_quoted(data->line[i]))
			i += quotes(data, data->line + i, data->line[i]);
		else if (data->line[i] == EXPAND_)
			i += expand(data, data->line + i);
		else if (is_keyword(data->line[i]))
			i += keyword(data, data->line + i);
		else if (is_special_op(data->line[i]))
			i += special_op(data, data->line + i, data->line[i]);
	}
}

t_tokens	*lexer(t_data *data)
{
	t_tokens	*head;

	head = NULL;
	if (white_check(data->line))
	{
		init_tokens_list(data);
		head = data->tokens;
		tokenize_line(data);
	}
	free(data->line);
	data->tokens = head;
	return (head);
}

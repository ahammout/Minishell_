/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 03:31:28 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/08 21:41:36 by ahammout         ###   ########.fr       */
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

int	expand(t_data *data, char *lexem)
{
	t_ref	ref;

	ref.i = 0;
	ref.j = 0;
	data->tokens->lex = malloc(sizeof(char) * (expand_size(lexem) + 1));
	if (!data->tokens->lex)
		exit_minishell(data, "Minishell: Allocation failed.");
	while (lexem[ref.i] == EXPAND_ || lexem[ref.i] == '@' \
		|| lexem[ref.i] == '*')
		data->tokens->lex[ref.j++] = lexem[ref.i++];
	while (ft_isalpha(lexem[ref.i]) || ft_isdigit(lexem[ref.i]) \
		|| lexem[ref.i] == '_' || lexem[ref.i] == '?')
		data->tokens->lex[ref.j++] = lexem[ref.i++];
	data->tokens->lex[ref.j] = '\0';
	if (is_quoted(lexem[ref.i]) || lexem[ref.i] == EXPAND_ \
		|| is_keyword(lexem[ref.i]))
		data->tokens->attach = 1;
	data->tokens->type = EXPAND_;
	return (ref.i);
}

int	quotes(t_data *data, char *lexem, char type)
{
	t_ref	ref;
	int		quote;

	ref.i = 0;
	ref.j = 0;
	data->tokens->lex = malloc(sizeof(char) * (quotes_size(lexem, type) + 1));
	if (!data->tokens->lex)
		exit_minishell(data, "Minishell: Allocation failed.");
	quote = 0;
	while (lexem[ref.i])
	{
		if (lexem[ref.i] == type)
			quote++;
		data->tokens->lex[ref.j++] = lexem[ref.i++];
		if (quote == 2)
			break ;
	}
	data->tokens->lex[ref.j] = '\0';
	if (is_quoted(lexem[ref.i]) || lexem[ref.i] == EXPAND_ \
		|| is_keyword(lexem[ref.i]))
		data->tokens->attach = 1;
	data->tokens->type = type;
	return (ref.i);
}

t_tokens	*lexer(t_data *data)
{
	t_tokens	*head;
	t_ref		ref;

	head = NULL;
	if (white_check (data->buffer))
	{
		ref.i = 0;
		ref.l = 0;
		init_tokens_list(data);
		head = data->tokens;
		while (data->buffer[ref.i] && white_check (data->buffer + ref.i))
		{
			create_new_node(data, &ref.l);
			while (is_whitespace(data->buffer[ref.i]))
				ref.i++;
			if (is_quoted(data->buffer[ref.i]))
				ref.i += quotes(data, data->buffer + ref.i, data->buffer[ref.i]);
			else if (data->buffer[ref.i] == EXPAND_)
				ref.i += expand(data, data->buffer + ref.i);
			else if (is_keyword(data->buffer[ref.i]))
				ref.i += keyword(data, data->buffer + ref.i);
			else if (is_special_op(data->buffer[ref.i]))
				ref.i += special_op(data, data->buffer + ref.i, data->buffer[ref.i]);
		}
	}
	free(data->buffer);
	data->tokens = head;
	return (head);
}

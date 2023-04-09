/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:26:46 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 04:00:02 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	quotes_size(char *lexem, char type)
{
	int	s;
	int	q;

	s = 0;
	q = 0;
	while (lexem[s])
	{
		if (lexem[s] == type)
			q++;
		s++;
		if (q == 2)
			break ;
	}
	return (s);
}

int quotes(t_data *data, char *lexem, char type)
{
	t_ref ref;
	int quote;

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
			break;
	}
	data->tokens->lex[ref.j] = '\0';
	if (is_quoted(lexem[ref.i]) || lexem[ref.i] == EXPAND_ || is_keyword(lexem[ref.i]))
		data->tokens->attach = 1;
	data->tokens->type = type;
	return (ref.i);
}

int	expand_size(char *lexem)
{
	int	s;

	s = 0;
	while (lexem[s] == EXPAND_ || lexem[s] == '@' \
		|| lexem[s] == '*')
		s++;
	while (ft_isalpha(lexem[s]) || ft_isdigit(lexem[s]) \
		|| lexem[s] == '_' || lexem[s] == '?')
		s++;
	return (s);
}

int expand(t_data *data, char *lexem)
{
	t_ref ref;

	ref.i = 0;
	ref.j = 0;
	data->tokens->lex = malloc(sizeof(char) * (expand_size(lexem) + 1));
	if (!data->tokens->lex)
		exit_minishell(data, "Minishell: Allocation failed.");
	while (lexem[ref.i] == EXPAND_ || lexem[ref.i] == '@' || lexem[ref.i] == '*')
		data->tokens->lex[ref.j++] = lexem[ref.i++];
	while (ft_isalpha(lexem[ref.i]) || ft_isdigit(lexem[ref.i]) || lexem[ref.i] == '_' || lexem[ref.i] == '?')
		data->tokens->lex[ref.j++] = lexem[ref.i++];
	data->tokens->lex[ref.j] = '\0';
	if (is_quoted(lexem[ref.i]) || lexem[ref.i] == EXPAND_ || is_keyword(lexem[ref.i]))
		data->tokens->attach = 1;
	data->tokens->type = EXPAND_;
	return (ref.i);
}
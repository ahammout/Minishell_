/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:23:06 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/08 16:11:47 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *inclosed_quotes(char *input)
{
	char *error;

	error = ft_strjoin("Minishell: ", input);
	error = ft_strjoin (error, ": Inclosed quotes.");
	return (error);
}

void    abs_syntax(t_data *data, int lexem_len, int n_quotes)
{
	t_ref   ref;
	char    *lexem;

	ref.i = 0;
	ref.j = 0;
	lexem = ft_strdup(data->tokens->lex);
	free(data->tokens->lex);
	if ((lexem_len - n_quotes) == 0)
	{
		data->tokens->lex = NULL;
		data->tokens->type = EMPTY;
	}
	else
	{
		data->tokens->lex = malloc(sizeof(char) * (lexem_len - n_quotes) + 1);
		if (!data->tokens->lex)
			exit_minishell(data, "Minishell: Allocation failed.");
		while (lexem[ref.i] == data->tokens->type)
			ref.i++;
		while (lexem[ref.i] && lexem[ref.i] != data->tokens->type)
			data->tokens->lex[ref.j++] = lexem[ref.i++];
		data->tokens->lex[ref.j] = '\0';
	}
	free (lexem);
}

int quotes_syntax(char *lexem, int type)
{
	int i;
	int n_q;

	i = 0;
	n_q = 0;
	while (lexem[i])
	{
		if (lexem[i] == type)
			n_q++;
		i++;
	}
	if (n_q == 2)
		return (n_q);
	return (-1);
}

int analyze_quotes(t_data *data)
{
	int n_q;

	if (data->tokens->type == DQUOTE || data->tokens->type == SQUOTE)
	{
		n_q = quotes_syntax (data->tokens->lex, data->tokens->type);
		if (n_q == -1)
			data->err = inclosed_quotes(data->tokens->lex);
		if (!data->err)
		{
			abs_syntax(data, ft_strlen(data->tokens->lex), n_q);
			if (data->tokens->lex)
			{
				if (ft_strchr(data->tokens->lex, DQUOTE) || data->tokens->type == SQUOTE \
					|| data->tokens->prev->type == HEREDOC)
				{
					data->tokens->type = KEYWORD;   
					return (0);
				}
				data->tokens->type = KEYWORD;
				if (ft_strchr(data->tokens->lex, EXPAND_))
					split_token(data);
			}
		}
	}
	return (0);
}

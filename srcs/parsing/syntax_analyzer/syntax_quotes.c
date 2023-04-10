/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:23:06 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 20:17:25 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	abs_syntax(t_data *data, int lexem_len, int n_quotes)
{
	t_ref	ref;
	char	*lexem;

	ref.i = 0;
	ref.j = 0;
	lexem = ft_strdup(data->tokens->lex);
	free(data->tokens->lex);
	if ((lexem_len - n_quotes) == 0)
	{
		data->tokens->lex = ft_strdup("");
		data->tokens->type = KEYWORD;
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

char	*inclosed_quotes(char *input)
{
	char	*error;

	error = ft_strjoin("Minishell: ", input);
	error = ft_strjoin_free1(error, ": Inclosed quotes.");
	return (error);
}

int	quotes_syntax(t_data *data, char *lexem, int type)
{
	int	i;
	int	n_q;

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
	else
		data->err = inclosed_quotes(data->tokens->lex);
	return (-1);
}

int	analyze_quotes(t_data *data)
{
	int	n_q;

	if (data->tokens->type == DQUOTE || data->tokens->type == SQUOTE)
	{
		n_q = quotes_syntax (data, data->tokens->lex, data->tokens->type);
		if (!data->err)
		{
			abs_syntax(data, ft_strlen(data->tokens->lex), n_q);
			if (data->tokens->lex)
			{
				if (ft_strchr(data->tokens->lex, DQUOTE) \
					|| data->tokens->type == SQUOTE \
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

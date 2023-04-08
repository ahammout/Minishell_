/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:46:54 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/08 16:10:28 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	optype(t_data *data, int type)
{
	if (data->tokens->lenght == 1 && type == REDOUT)
		data->tokens->type = REDOUT;
	else if (data->tokens->lenght > 1 && type == REDOUT)
		data->tokens->type = APPEND;
	else if (data->tokens->lenght == 1 && type == REDIN)
		data->tokens->type = REDIN;
	else if (data->tokens->lenght > 1 && type == REDIN)
	{
		data->heredoc = 1;
		data->tokens->type = HEREDOC;
	}
	else if (type == PIPE)
		data->tokens->type = PIPE;
}

int	is_special_op(char c)
{
	if (c == REDIN || c == REDOUT || c == PIPE)
		return (1);
	return (0);
}

int	is_whitespace(char c)
{
	if ((c == ' ' || c == '\t'))
		return (1);
	return (0);
}

int	is_quoted(char c)
{
	if ((c == DQUOTE || c == SQUOTE))
		return (1);
	return (0);
}

int	is_keyword(char c)
{
	if (!is_quoted(c) && !is_special_op(c)
		&& !is_whitespace(c) && c != EXPAND_
		&& c != '\0')
		return (1);
	return (0);
}

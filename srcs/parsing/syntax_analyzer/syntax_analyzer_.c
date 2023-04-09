/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:47:07 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 17:27:14 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	analyze_begin(t_data *data)
{
	if (!data->err)
	{
		if (data->tokens->lex)
		{
			if ((data->tokens->lex[0] == PIPE || data->tokens->type == HEREDOC \
				|| data->tokens->type == REDIN) && !data->tokens->next)
			{
				data->err = ft_strdup("Minishell: syntax error near `");
				data->err = ft_strjoin_free1(data->err, "newline'");
				if (data->err && data->heredoc)
					data->heredoc = 0;
			}
		}
	}
}

void	analyze_end(t_data *data)
{
	if (!data->err)
	{
		if (data->tokens->lex)
		{
			if ((data->tokens->type == PIPE || data->tokens->type == HEREDOC \
				|| data->tokens->type == REDIN || data->tokens->type == REDOUT \
				|| data->tokens->type == APPEND) && !data->tokens->next)
			{
				data->err = ft_strdup("Minishell: syntax error near `");
				data->err = ft_strjoin_free1(data->err, "newline'");
				if (data->err && data->heredoc)
					data->heredoc = 0;
			}
		}
	}
}

void	analyze_filename(t_data *data)
{
	char	*filename;

	if (!data->err)
	{
		if (data->tokens->lex)
		{
			if ((data->tokens->type == PIPE || data->tokens->type == HEREDOC \
				|| data->tokens->type == REDIN || data->tokens->type == REDOUT \
				|| data->tokens->type == APPEND) \
				&& data->tokens->next->type != KEYWORD)
			{
				filename = ft_strdup(data->tokens->next->lex);
				data->err = ft_strdup("Minishell: syntax error near `");
				data->err = ft_strjoin_free1(data->err, filename);
				data->err = ft_strjoin_free1(data->err, "'");
				if (data->err && data->heredoc)
					data->heredoc = 0;
				free(filename);
			}
		}
	}
}

int	is_metecharacter(int type)
{
	if (type == REDIN || type == REDOUT || type == APPEND \
		|| type == HEREDOC || type == PIPE)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 syntax_analyzer_.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: ahammout <ahammout@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2023/02/02 18:11:47 by ahammout		   #+#	  #+#			  */
/*	 Updated: 2023/04/08 21:03:53 by ahammout		  ###	########.fr		  */
/*																			  */
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
				if (data->tokens->type == HEREDOC)
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
				|| data->tokens->type == REDIN || data->tokens->type == REDOUT
				|| data->tokens->type == APPEND) && !data->tokens->next)
				{
					data->err = ft_strdup("Minishell: syntax error near `");
					data->err = ft_strjoin_free1(data->err, "newline'");
					data->heredoc = 0;
				}
		}
	}
}

void	analyze_filename(t_data *data)
{
	if (!data->err)
	{
		if (data->tokens->lex)
		{
			if ((data->tokens->type == PIPE || data->tokens->type == HEREDOC \
				|| data->tokens->type == REDIN || data->tokens->type == REDOUT
				|| data->tokens->type == APPEND) && data->tokens->next->type != KEYWORD)
				{
					data->err = ft_strdup("Minishell: syntax error near `");
					data->err = ft_strjoin_free1(data->err, ft_strjoin(data->tokens->next->lex, "'"));
					if (data->tokens->type == HEREDOC)
						data->heredoc = 0;
				}
		}
	}
}

int is_metecharacter(int type)
{
	if (type == REDIN || type == REDOUT || type == APPEND \
		|| type == HEREDOC || type == PIPE)
		return (1);
	return (0);
}

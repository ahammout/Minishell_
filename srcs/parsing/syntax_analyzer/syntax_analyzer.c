/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:46:56 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 14:49:19 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	analyze_redirections(t_data *data)
{
	if (!data->err)
	{
		if (data->tokens->type == REDOUT || data->tokens->type == APPEND \
			|| data->tokens->type == REDIN || data->tokens->type == HEREDOC)
		{
			if (data->tokens->lenght > 2 || !data->tokens->next)
			{
				data->err = ft_strdup("Minishell: syntax error near `");
				data->err = ft_strjoin_free1(data->err, "newline'");
				if (data->tokens->type == HEREDOC)
					data->heredoc = 0;
			}
			analyze_filename(data);
		}
	}
}

void	analyze_pipe(t_data *data)
{
	if (data->tokens->type == PIPE && !data->err)
	{
		if (data->tokens->lenght > 1 || data->tokens->next == NULL)
		{
			data->err = ft_strdup("Minishell: syntax error near `");
			data->err = ft_strjoin_free1(data->err, "|'");
		}
	}
}

void	analyze_begin_end(t_data *data)
{
	t_tokens	*head;

	head = data->tokens;
	analyze_begin(data);
	if (data->tokens->next && !data->err)
	{
		while (data->tokens->next && !is_metecharacter(data->tokens->type))
			data->tokens = data->tokens->next;
		if (data->tokens->next == NULL)
			analyze_end(data);
	}
	data->tokens = head;
}

t_tokens	*syntax_analyzer(t_data *data)
{
	t_tokens	*head;

	head = data->tokens;
	analyze_begin_end(data);
	while (data->tokens != NULL && !data->err)
	{
		analyze_quotes(data);
		analyze_pipe(data);
		analyze_redirections(data);
		data->tokens = data->tokens->next;
	}
	data->tokens = head;
	if (data->err && !data->heredoc)
		return (generate_error(data), free_data(data), (void *)0);
	return (head);
}

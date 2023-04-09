/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 03:26:45 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 04:06:14 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_data(t_data *data)
{
	free_tokens_list(data);
	free_cmds_list(data);
	if (data->err)
		free(data->err);
}

void	exit_minishell(t_data *data, char *err)
{
	if (data->line)
		free(data->line);
	free_env_list(data);
	free_tokens_list(data);
	free_cmds_list(data);
	if (err)
	{
		ft_putstr_fd(err, 2);
		exit(EXIT_FAILURE);
	}
	exit(g_exit_status);
}

int	free_cmds_list(t_data *data)
{
	t_exec	*curr;
	t_exec	*prev;

	curr = data->cmds;
	prev = NULL;
	if (curr == NULL)
		return (0);
	while (curr != NULL)
	{
		if (curr->str)
			free_array(curr->str);
		if (curr->cmd_status)
			free(curr->cmd_status);
		if (curr->in_file != 0)
			close(curr->in_file);
		if (curr->out_file != 1)
			close(curr->out_file);
		prev = curr;
		curr = curr->next;
		free(prev);
		prev = NULL;
	}
	data->cmds = NULL;
	return (0);
}

int	free_tokens_list(t_data *data)
{
	t_tokens	*tmp;

	while (data->tokens != NULL)
	{
		free(data->tokens->lex);
		tmp = data->tokens;
		data->tokens = data->tokens->next;
		free(tmp);
	}
	data->tokens = NULL;
	return (0);
}

int	free_env_list(t_data *data)
{
	t_env	*tmp;

	while (data->env)
	{
		free(data->env->name);
		free(data->env->value);
		tmp = data->env;
		data->env = data->env->next;
		free(tmp);
	}
	data->env = NULL;
	return (0);
}

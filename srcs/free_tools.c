/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:59:17 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/07 15:14:32 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_data(t_data *data)
{
	free_tokens_list(data);
    free_cmds_list(data);
    if (data->err)
		free(data->err);
}

void exit_minishell(t_data *data, char *err)
{
    if (data->buffer)
		free(data->buffer);
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

int free_cmds_list(t_data *data)
{
    t_exec *tmp;
    int     i;

    while (data->cmds)
    {
		i = 0;
		if (data->cmds->str)
		{
			while (data->cmds->str[i])
			{
				free(data->cmds->str[i]);
				i++;
			}
			free(data->cmds->str);
		}
		if (data->cmds->in_file != 0)
			close(data->cmds->in_file);
		if (data->cmds->out_file != 1)
			close(data->cmds->out_file);
		tmp = data->cmds;
		data->cmds = data->cmds->next;
		free(tmp);
    }
    data->cmds = NULL;
    return (0);
}

int free_tokens_list(t_data *data)
{
    t_tokens *tmp;

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

int free_env_list(t_data *data)
{
    t_env *tmp;
	
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

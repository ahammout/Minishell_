/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:51:40 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/08 15:51:49 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	fill_value(t_data *data, char *envp)
{
	t_ref	ref;

	ref.l = 1;
	ref.j = 1;
	ref.i = 0;
	while (envp[ref.l])
		ref.l++;
	data->env->value = malloc(sizeof(char) * (ref.l));
	if (!data->env->value)
		exit_minishell(data, "Minishell: Allocation failed.");
	while (envp[ref.j])
		data->env->value[ref.i++] = envp[ref.j++];
	data->env->value[ref.i] = '\0';
	return (ref.j);
}

int	fill_name(t_data *data, char *envp)
{
	t_ref	ref;

	ref.l = 0;
	ref.i = 0;
	ref.j = 0;
	while (envp[ref.l] != '=')
		ref.l++;
	data->env->name = malloc(sizeof(char) * (ref.l + 1));
	if (!data->env->name)
		exit_minishell(data, "Minishell: Allocation failed.");
	while (envp[ref.j] != '=')
		data->env->name[ref.i++] = envp[ref.j++];
	data->env->name[ref.i] = '\0';
	return (ref.j);
}

void	add_node(t_data *data, int *new_node)
{
	t_env	*node;

	node = NULL;
	if (*new_node)
	{
		node = malloc(sizeof(t_env));
		if (!node)
			exit_minishell(data, "Minishell: Allocation failed.");
		node->next = NULL;
		data->env->next = node;
		data->env = data->env->next;
	}
	else
		*new_node = 1;
}

void	init_env_list(t_data *data, char **envp)
{
	data->envp_ = envp;
	data->env = malloc(sizeof(t_env));
	if (!data->env)
		exit_minishell(data, "Minishell: Allocation failed.");
	data->env->name = NULL;
	data->env->value = NULL;
	data->env->next = NULL;
}

void	set_environment(t_data *data, char **envp)
{
	t_env	*head;
	t_ref	ref;

	if (envp[0])
	{
		init_env_list(data, envp);
		head = data->env;
		ref.i = 0;
		ref.j = 0;
		ref.l = 0;
		while (envp[ref.i])
		{
			add_node(data, &ref.l);
			ref.j = 0;
			while (envp[ref.i][ref.j])
			{
				ref.j += fill_name(data, envp[ref.i] + ref.j);
				ref.j += fill_value(data, envp[ref.i] + ref.j);
			}
			ref.i++;
		}
		data->env = head;
	}
	else
		set_environment_beta(data);
}

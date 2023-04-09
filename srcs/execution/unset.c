/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:14:55 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/09 15:17:01 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	unset_last_node(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next->next)
		tmp = tmp->next;
	free(tmp->next->name);
	if (tmp->next->value)
		free(tmp->next->value);
	free(tmp->next);
	tmp->next = NULL;
}

static t_env	*find_env_node_unset(char *name, t_data *data)
{
	t_env	*env;
	t_env	*node;

	env = data->env;
	node = NULL;
	if (!ft_strcmp(env->name, name))
	{
		node = data->env;
		data->env = env->next;
		return (node);
	}
	while (env->next)
	{
		if (!ft_strcmp(env->next->name, name))
		{
			node = env->next;
			env->next = env->next->next;
			return (node);
		}
		env = env->next;
	}
	if (!ft_strcmp(env->name, name))
		return (unset_last_node(data->env), NULL);
	return (NULL);
}

void	free_env_node(t_env *node)
{
	free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	ft_unset(t_exec *cmd, t_data *data)
{
	int		i;
	t_env	*node;

	node = NULL;
	i = 1;
	if (!data->env)
		return (g_exit_status = 0, (void)0);
	while (cmd->str[i])
	{
		if (!error_in(cmd->str[i]))
		{
			node = find_env_node_unset(cmd->str[i], data);
			if (node)
				free_env_node(node);
			g_exit_status = 0;
		}
		else
		{
			g_exit_status = 1;
			ft_putstr_fd("Minishell: unset: `", 2);
			ft_putstr_fd(cmd->str[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
}

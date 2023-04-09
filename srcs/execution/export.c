/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:24:41 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/09 15:37:18 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	append_env(t_data *data, const char *name, const char *val)
{
	char	*new_val;
	size_t	new_val_len ;
	t_env	*node;
	t_env	*new_node;

	node = find_env_node(data->env, name);
	if (node)
	{
		if (node->value)
		{
			new_val_len = ft_strlen(node->value) + ft_strlen(val);
			new_val = malloc(new_val_len + 1);
			ft_strlcpy(new_val, node->value, new_val_len + 1);
			ft_strlcat(new_val, val, new_val_len + 1);
			free(node->value);
			node->value = new_val;
		}
		else
			node->value = ft_strdup(val);
	}
	else
	{
		new_node = new_env_node(ft_strdup(name), ft_strdup(val));
		add_back_env_node(&data->env, new_node);
	}
}

t_env	*new_env_node(char *name, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	add_back_env_node(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (!env || !new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	export1(t_data *data, char *name, char *value, bool append)
{
	t_env	*node;

	if (append)
	{
		append_env(data, name, value);
		return ;
	}
	node = find_env_node(data->env, name);
	if (node)
	{
		if (value)
		{
			free(node->value);
			node->value = ft_strdup(value);
		}
	}
	else
	{
		if (value)
			add_back_env_node(&data->env,
				new_env_node(ft_strdup(name), ft_strdup(value)));
		else
			add_back_env_node(&data->env,
				new_env_node(ft_strdup(name), NULL));
	}
}

void	ft_export(t_data *data, t_exec *cmd)
{
	char	*name;
	char	*value;
	int		i;
	bool	append;

	i = 1;
	if (cmd->str[1] == NULL)
	{
		export0(data);
		g_exit_status = 0;
		return ;
	}
	while (cmd->str[i])
	{
		append = false;
		name = extract_name(cmd->str[i], &append);
		if (!name)
			return ;
		value = extract_value(cmd->str[i]);
		export1(data, name, value, append);
		free(name);
		free(value);
		i++;
	}
}

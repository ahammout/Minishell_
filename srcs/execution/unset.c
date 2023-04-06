/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:14:55 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/05 17:38:12 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	unset_last_node(t_env *env)
{
	t_env   *tmp;

	tmp = env;
    while (tmp->next->next)
        tmp = tmp->next;
	free(tmp->next->name);
    if (tmp->next->value)
		free(tmp->next->value);
	free(tmp->next);
	tmp->next = NULL;
}

// Find the node in the linked list with the given name and return it, or NULL if not found
t_env	*find_env_node(char *name, t_data *data)
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

// Free the memory allocated for an environment node
void	free_env_node(t_env *node)
{
	free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}
// Remove environment variables specified in the command
void	ft_unset(t_exec *cmd, t_data *data)
{
    int	i;
	
	i = 1;
    t_env *node = NULL;
    if (!data->env)
        return (exitS = 0, (void)0);
    while (cmd->str[i])
	{
		if (!error_in(cmd->str[i]))
		{
			node = find_env_node(cmd->str[i], data);
			if (node)
                free_env_node(node);
        }
		else
		{
			exitS = 1598;
			ft_putstr_fd("invalid identifier \n", 2);
		}
		i++;
	}
	if (exitS == 1598)
        exitS = 1;
	else
		exitS = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 01:37:04 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/08 02:04:12 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_eq(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

void	export0(t_data *data)
{
	t_env	*tmp;
	t_env	*head;

	tmp = sort_environment(data);
	head = tmp;
	   while (head)
	{
		ft_putstr_fd("declare -x ", data->cmds->out_file);
		ft_putstr_fd(head->name, data->cmds->out_file);
		if (head->value)
		{
			ft_putstr_fd("=\"", data->cmds->out_file);
			ft_putstr_fd(head->value, data->cmds->out_file);
			ft_putstr_fd("\"",data->cmds->out_file); 
		}
		ft_putstr_fd("\n", data->cmds->out_file);
		head = head->next;
	}
	free_env(tmp);
}

t_env	*str_to_list(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		tmp->name = ft_substr(envp[i], 0, find_eq(envp[i]));
		if ((unsigned int)find_eq(envp[i]) == ft_strlen(envp[i]))
			tmp->value = NULL;
		else
			tmp->value = ft_substr(envp[i], find_eq(envp[i]) + 1,
					ft_strlen(envp[i]) - find_eq(envp[i]));
		tmp->next = env;
		env = tmp;
		i++;
	}
	return (env);
}

void	print_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (tmp->value)
		{
			{
				ft_putstr_fd(tmp->name, data->cmds->out_file);
				ft_putstr_fd("=", data->cmds->out_file);
				ft_putstr_fd(tmp->value, data->cmds->out_file);
				ft_putstr_fd("\n", data->cmds->out_file);
			}
		}
		tmp = tmp->next;
	}
}
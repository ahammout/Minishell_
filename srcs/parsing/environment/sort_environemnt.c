/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_environemnt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:58:36 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/08 01:39:37 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	**fill_envp(char **envp, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value)
		{
			envp[i] = ft_strjoin(env->name, "=");
			envp[i] = ft_strjoin(envp[i], env->value);
		}
		else
			envp[i] = ft_strdup(env->name);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

// while (tmp)
// 	{
// 		if (tmp->name && tmp->value)
// 		{
// 			tmp2 = ft_strjoin(tmp->name, "=");
// 			envp[i] = ft_strjoin_free1(tmp2, tmp->value);
// 		}
// 		else if (!tmp->value)
// 			envp[i] = ft_strdup(tmp->name);
// 		else
// 			break ;
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	envp[i] = NULL;

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

static char	**sort_env(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strcmp(envp[i], envp[j]) < 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}

char	**list_to_str(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*tmp;
	char	*tmp2;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = env;
	envp = fill_envp(envp, tmp);
	return (envp);
}

t_env	*sort_environment(t_data *data)
{
	char	**envp;
	t_env	*tmp;

	envp = list_to_str(data->env);
	tmp = str_to_list(sort_env(envp));
	free_array(envp);
	return (tmp);
}

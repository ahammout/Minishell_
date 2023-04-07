/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 06:02:03 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/06 21:51:13 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_exit_status;

int	check_append(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=' && str[i - 1] == '+')
		return (1);
	return (0);
}

char	*extract_name(char *str, bool *append)
{
	int		i;
	char	*name;

	i = 1;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=' && check_append(str))
		*append = true;
	if (*append)
		name = ft_substr(str, 0, i - 1);
	else
		name = ft_substr(str, 0, i);
	if (error_in(name))
	{
		g_exit_status = 1;
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_exit_status = 1;
		return (NULL);
	}
	return (name);
}

char	*extract_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (ft_substr(str, i + 1, ft_strlen(str) - i));
	return (NULL);
}

int	error_in(const char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
	}
	return (0);
}

t_env	*find_env_node(t_env *env, const char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

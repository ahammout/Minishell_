/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:13:54 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/08 16:00:13 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	update_size(char *lexem, char *pids, char *value, char *e_status)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (lexem && (ft_isdigit(lexem[i]) || lexem[i] == '@' \
		|| lexem[i] == '*' || lexem[i] == '?'))
	{
		i++;
		while (lexem[i])
		{
			len++;
			i++;
		}
	}
	if (value)
		return ((ft_strlen(pids)) + ft_strlen(value));
	else if (e_status)
		return (len + ft_strlen(pids) + ft_strlen(e_status));
	return (len + (ft_strlen(pids)));
}

char	*get_value(t_data *data, char *var)
{
	t_env	*head;
	char	*value;

	value = NULL;
	head = data->env;
	if (!var)
		return (0);
	while (data->env)
	{
		if (ft_strcmp(var, data->env->name) == 0)
		{
			value = ft_strdup(data->env->value);
			break ;
		}
		data->env = data->env->next;
	}
	free(var);
	data->env = head;
	return (value);
}

char	*get_var(t_data *data, char *lexem)
{
	int		i;
	int		len;
	char	*var;

	len = 0;
	i = 0;
	while (lexem[len] && (ft_isalpha(lexem[len]) \
		|| ft_isdigit(lexem[len]) || lexem[len] == '_' \
		|| lexem[len] == '@' || lexem[len] == '*'))
		len++;
	var = malloc(sizeof(char) * len + 1);
	if (!var)
		exit_minishell(data, "Minishell: Allocation failed.");
	while (lexem[i] && (ft_isalpha(lexem[i]) \
		|| ft_isdigit(lexem[i]) || lexem[i] == '_' \
		|| lexem[i] == '@' || lexem[len] == '*'))
	{
		var[i] = lexem[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

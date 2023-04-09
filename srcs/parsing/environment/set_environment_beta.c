/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environment_beta.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:09:12 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 15:17:27 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	set_environment_beta(t_data *data)
{
	data->env = (t_env *)malloc(sizeof(t_env));
	data->env->name = ft_strdup("PWD");
	data->env->value = getcwd(NULL, 0);
	data->env->next = (t_env *)malloc(sizeof(t_env));
	data->env->next->name = ft_strdup("OLDPWD");
	data->env->next->value = NULL;
	data->env->next->next = (t_env *)malloc(sizeof(t_env));
	data->env->next->next->name = ft_strdup("SHLVL");
	data->env->next->next->value = ft_strdup("0");
	data->env->next->next->next = (t_env *)malloc(sizeof(t_env));
	data->env->next->next->next->name = ft_strdup("PATH");
	data->env->next->next->next->value
		= ft_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	data->env->next->next->next->next = NULL;
}

void	display_environment(t_data *data)
{
	t_env	*head;
	int		index;

	head = data->env;
	index = 0;
	while (head != NULL)
	{
		printf("--------------	Node %d	-----------\n\n", index);
		printf(" *Name: %s\n", head->name);
		printf(" *Value: %s\n\n", head->value);
		index++;
		head = head->next;
	}
}

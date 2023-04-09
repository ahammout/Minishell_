/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_04.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 06:43:28 by zessadqu          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/08 23:39:30 by zessadqu         ###   ########.fr       */
=======
/*   Updated: 2023/04/09 01:34:04 by zessadqu         ###   ########.fr       */
>>>>>>> 7ee4a774096231491bee4b55f99abeb926e1152e
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr_free1(char *s1, int start, int end)
{
	char	*str;

	if (!s1)
		return (NULL);
	else
	{
		str = ft_substr(s1, start, end);
		free(s1);
		return (str);
	}
}

void	check_bash(char *path, t_exec *exc, char **envp)
{
	char	*shell;
	char	**tmp2;
	int		i;

	i = 0;
	shell = getenv("SHELL");
	if (!shell)
		shell = ft_strdup("/bin/bash");
	while (exc->str[i])
		i++;
	tmp2 = malloc(sizeof(char *) * (i + 4));
	i = 0;
	tmp2[i++] = ft_strdup(shell);
	tmp2[i++] = ft_strdup("-c");
	tmp2[i++] = ft_strdup(path);
	while (exc->str[i - 3])
	{
		tmp2[i] = ft_strdup(exc->str[i - 3]);
		i++;
	}
	tmp2[i] = NULL;
	if (execve(shell, tmp2, envp) == -1)
		return (g_exit_status = 127, perror("Minishell "));
}

void	free_env(t_env *env)
{
	t_env	*tmp;
	
	while (env)
	{
		free(env->name);
		free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	error_display(t_exec *tmp)
{
	ft_putstr_fd(tmp->cmd_status, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 1;
}

void	is_empty(t_data *data, t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec->str)
		return;
	if (exec->str[0][0] == '\0')
		is_no_cmd(data, exec);
}

void	error_display(t_exec *tmp)
{
	ft_putstr_fd(tmp->cmd_status, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 1;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_04.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 06:43:28 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/06 17:39:09 by zessadqu         ###   ########.fr       */
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
	char	*tmp;
	char	**tmp2;
	int		i;

	shell = getenv("SHELL");
	if (!shell)
		shell = ft_strdup("/bin/bash");
	while(exc->str[i])
		i++;
	tmp2 = malloc(sizeof(char *) * (i + 3));
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
	execve(shell, tmp2, envp);
}
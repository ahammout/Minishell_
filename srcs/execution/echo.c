/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:55:15 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/04 03:47:15 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	option(t_exec	*exec, bool	*mode)
{
	int		i;
	int		j;
	t_exec	*tmp;

	i = 0;
	j = 0;
	tmp = exec;
	*mode = false;
	while (exec->str[++i])
	{
		j = 0;
		if (exec->str[i][j++] == '-' && exec->str[i][1] == 'n')
		{
			while (exec->str[i][j] == 'n')
				j++;
			if (!exec->str[i][j])
				*mode = true;
			else
				return (i);
		}
		else
			break ;
	}
	return (i);
}

void	ft_echo(t_exec	*exec)
{
	int		i;
	bool	mode;

	i = option(exec, &mode);
	if (!exec->str[1])
	{
		if (!mode)
			return (ft_putstr_fd("\n", exec->out_file), (void)0);
		else
			return ;
	}
	while (exec->str[i])
	{
		ft_putstr_fd(exec->str[i], exec->out_file);
		if (exec->str[i + 1])
			ft_putstr_fd(" ", exec->out_file);
		i++;
	}
	if (!mode)
		ft_putstr_fd("\n", exec->out_file);
	exitS = 0;
}
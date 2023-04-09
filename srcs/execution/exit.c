/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 00:06:12 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/09 15:41:57 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_exec	*cmd)
{
	int	i;
	int	exst;

	i = 0;
	if (cmd->str[1])
	{
		if (cmd->str[2])
			return (g_exit_status = 1, ft_putstr_fd("exit\ntoo many arguments\n",
					2));
		while (cmd->str[1][i])
		{
			if (!ft_isdigit(cmd->str[1][i]))
			{
				ft_putstr_fd("Numeric argument required\n", 2);
				exit (1);
			}
			else
			{
				exst = ft_atoi(cmd->str[1]);
				exit((char)exst);
			}
		}
		i++;
	}
	exit(0);
}

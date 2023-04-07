/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_03.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 06:32:53 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/07 00:03:07 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern  int  g_exit_status;

void	executable_f(t_data *data, char **tmp)
{
	execute_command(data, data->cmds, data->cmds->str[0], tmp);
	free_array(tmp);
	free_data(data);
}

void	is_directory(t_data *data, t_exec *tmp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tmp->str[0], 2);
	ft_putstr_fd(": is a directory	", 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 126;
	free_data(data);
}

void	is_perms(t_data *data, t_exec *tmp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tmp->str[0], 2);
	ft_putstr_fd(": Permission denied	", 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 126;
	free_data(data);
}

void	is_no_such_file(t_data *data, t_exec *tmp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tmp->str[0], 2);
	ft_putstr_fd(": No such file or directory	", 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 127;
	free_data(data);
}

void	is_no_cmd(t_data *data, t_exec *tmp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tmp->str[0], 2);
	ft_putstr_fd(": command not found	", 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 127;
	free_data(data);
}

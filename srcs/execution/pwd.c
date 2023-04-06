/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:06:56 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/06 06:57:18 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_exit_status;

int	ft_pwd(t_data *data)
{
	getcwd(data->path, PATH_MAX);
	ft_putendl_fd(data->path, data->cmds->out_file);
	g_exit_status = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:01:09 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/02 01:45:03 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_file(const char *filename) {
    struct stat filestat;

    if (stat(filename, &filestat) == -1) {
        return 4;
    }

    if (S_ISDIR(filestat.st_mode))
        return 1;
	else if (S_ISREG(filestat.st_mode))
	{
        if (filestat.st_mode & S_IXUSR)
            return 3;
		else
            return 2;
    }
	else
        return 4;
}

void	cmd_call(t_data *data, int her_file)
{
	int		i;
	int		check;
	char	*path;
	char	**tmp;
	int 	st;

	i = 0;
	check = count_pps(data->cmds);
	tmp = list_to_str(data->env);
	if (check)
    {
		data->pipex= malloc(sizeof(t_pipe));
		data->pipex->p_c = check;
		exec_pipes(data->cmds, data, her_file, data->envp_);
		free_array(tmp);
        free_data(data);
		return;
	}

	if (!data->cmds->str[0] || !builtin(data, data->cmds))
	{
		free_array(tmp);
        free_data(data);
		free_data(data);
		return ;
	}
	st = check_file(data->cmds->str[0]);
	path = get_path(data->cmds->str[0], data, &check);
	if (path)
	{
		execute_command(data->cmds, path, tmp);
		free_array(tmp);
		free(path);
		free_data(data);
		return ;
	}
	else if (st == 3 && ft_strncmp(data->cmds->str[0], "./", 2) == 0)
	{
		execute_command(data->cmds, data->cmds->str[0], tmp);
		free_array(tmp);
		free(path);
		free_data(data);
		return ;
	}
	 else if (st == 1 && ft_strncmp(data->cmds->str[0], "./", 2) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmds->str[0], 2);
		ft_putstr_fd(": is a directory	", 2);
		ft_putstr_fd("\n", 2);
		free_array(tmp);
		free(path);
		free_data(data);
	}
	 else if (st == 2 && ft_strncmp(data->cmds->str[0], "./", 2) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmds->str[0], 2);
		ft_putstr_fd(": Permission denied	", 2);
		ft_putstr_fd("\n", 2);
		free_array(tmp);
		free(path);
		free_data(data);
	}
	else
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(data->cmds->str[0], 2);
		ft_putstr_fd("\n", 2);
		free_array(tmp);
		free(path);
		free_data(data);
	}
	return ;
}
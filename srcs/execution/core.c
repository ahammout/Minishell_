/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:01:09 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/02 22:33:59 by zessadqu         ###   ########.fr       */
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
void	shell_cmd(t_data *data, char *path, char **tmp)
{
	execute_command(data->cmds, path, tmp);
	free_array(tmp);
	free(path);
	free_data(data);
}

void executable_f(t_data *data, char **tmp)
{
	execute_command(data->cmds, data->cmds->str[0], tmp);
	free_array(tmp);
	free_data(data);
}

void	is_directory(t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmds->str[0], 2);
	ft_putstr_fd(": is a directory	", 2);
	ft_putstr_fd("\n", 2);
	free_data(data);
}

void	is_perms(t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmds->str[0], 2);
	ft_putstr_fd(": Permission denied	", 2);
	ft_putstr_fd("\n", 2);
	free_data(data);
}

void is_no_such_file(t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmds->str[0], 2);
	ft_putstr_fd(": No such file or directory	", 2);
	ft_putstr_fd("\n", 2);
	free_data(data);
}

void	is_no_cmd(t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmds->str[0], 2);
	ft_putstr_fd(": command not found	", 2);
	ft_putstr_fd("\n", 2);
	free_data(data);
}

void	cmd_extra(t_data *data, char *path, char **tmp, int st)
{
	if (path)
		return(shell_cmd(data, path, tmp), (void)0) ;
	else if (st == 3 && ft_strncmp(data->cmds->str[0], "./", 2) == 0)
		return ( executable_f(data, tmp), free(path),(void)0) ;
	else if (st == 1 && ft_strncmp(data->cmds->str[0], "./", 2) == 0)
		return(is_directory(data), free_array(tmp), free(path), (void)0) ;
	else if (st == 2 && ft_strncmp(data->cmds->str[0], "./", 2) == 0)
		return(is_perms(data), free_array(tmp), free(path), (void)0) ;
	else if (st == 4 && ft_strncmp(data->cmds->str[0], "./", 2) == 0)
		return (is_no_such_file(data), free_array(tmp), free(path), (void)0) ;
	else
		return (is_no_cmd(data), free_array(tmp), free(path), (void)0);
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
		return (exec_pipes(data->cmds, data, her_file, data->envp_),
				free_array(tmp), free_data(data), (void)0);
	}

	if (!data->cmds->str[0] || !builtin(data, data->cmds))
		return (free_array(tmp),free_data(data),(void)0);
	st = check_file(data->cmds->str[0]);
	path = get_path(data->cmds->str[0], data, &check);
	return (cmd_extra(data, path, tmp, st), (void)0);
}

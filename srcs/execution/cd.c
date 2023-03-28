/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:15:39 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/28 15:53:14 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	change_to_home_directory(t_data *data, char *home_dir)
{
    char *cwd = getcwd(NULL, PATH_MAX);
    if (cwd == NULL)
    {
        perror("getcwd");
        return 1;
    }
    export1(data, "OLDPWD", cwd, false);
    if (chdir(home_dir) == -1)
    {
        perror(home_dir);
        free(cwd);
        return 1;
    }
    free(cwd);
    export1(data, "PWD", home_dir, false);
    return 0;
}

static int	change_to_directory(t_data *data, char *dir_path)
{
    char *cwd = getcwd(NULL, PATH_MAX);
    if (cwd == NULL)
    {
        perror("getcwd");
        return 1;
    }
    export1(data,"OLDPWD", cwd, false) ;
    if (chdir(dir_path) == -1)
    {
        perror(dir_path);
        free(cwd);
        return 1;
    }
    free(cwd);
    export1(data, "PWD", dir_path, false);
    return 0;
}

void	ft_cd(t_data *data)
{
    char *dir_path ;
    char *home_dir;
    t_exec *tmp;

    tmp = data->cmds;
    home_dir = getenv("HOME");
    if (!tmp->str[1] && ft_strcmp(tmp->str[0], "cd") == 0)
        exitS = change_to_home_directory(data, home_dir);
    else
    {
        dir_path = tmp->str[1];
        change_to_directory(data, dir_path);
    }
}

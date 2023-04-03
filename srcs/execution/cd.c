/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:15:39 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/03 22:01:23 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	change_to_home_directory(t_data *data, char *home_dir)
{
    char *cwd = getcwd(NULL, PATH_MAX);
    if (!home_dir || home_dir[0] == '\0')
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
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
    char *tmp;
    if ((!ft_strcmp(dir_path, "..") || !ft_strcmp(dir_path, ".")) && cwd == NULL)
    {
        exitS = 1;
        tmp = ft_strdup(dir_path);
        while (chdir(tmp) == -1)
        {
            tmp = ft_strjoin_free1(tmp, "../");
        }
        export1(data, "PWD", tmp, false);
        export1(data, "OLDPWD", dir_path, false);
        free(tmp);
        return(0) ;
    }
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
    home_dir = ft_getenv(data, "HOME");
    if (!tmp->str[1] && ft_strcmp(tmp->str[0], "cd") == 0)
        exitS = change_to_home_directory(data, home_dir);
    else
    {
        dir_path = tmp->str[1];
        change_to_directory(data, dir_path);
    }
}

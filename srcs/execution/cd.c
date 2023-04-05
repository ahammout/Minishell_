/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:15:39 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/05 04:05:41 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//cd: error retrieving current directory
int find_last_slash(char *str);

int   special_case(t_data *data, char  *tmp)
{
    if (data->check == 0)
    {
        perror("cd: error retrieving current directory");
        perror("getcwd");
        data->check++;
    }
    if(access(tmp, X_OK) !=-1)
        {
            chdir(tmp);
            export1(data, "PWD", tmp, false);
            export1(data, "OLDPWD", data->path, false);
            free(tmp);
            return (0);
        }
        else
        {
            tmp = ft_substr(tmp , 0, find_last_slash(tmp));
            special_case(data, tmp);
        }
}
int find_last_slash(char *str)
{
    int i;
    int last_slash;

    i = 0;
    last_slash = 0;
    while (str[i])
    {
        if (str[i] == '/')
            last_slash = i;
        i++;
    }
    return (last_slash);
}

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
        //free(cwd);
        return 1;
    }
    //free(cwd);
    export1(data, "PWD", home_dir, false);
    return 0;
}

static int	change_to_directory(t_data *data, char *dir_path)
{
    char *cwd;
    char *tmp;
    
    cwd = getcwd(data->path, PATH_MAX);
    tmp = ft_strdup(data->path);
    if ((!ft_strcmp(dir_path, "..") || !ft_strcmp(dir_path, ".")) && cwd == NULL)
    {
        special_case(data, tmp);
        return(0) ;
    }
    if (cwd == NULL)
    {
        perror("getcwd");
        return 1;
    }
    export1(data,"OLDPWD", data->path, false) ;
    if (chdir(dir_path) == -1)
    {
        perror(dir_path);
        free(cwd);
        return 1;
    }
    if (ft_strcmp(dir_path, "..") == 0)
    {
        tmp = ft_substr(data->path, 0, find_last_slash(data->path));
        export1(data, "PWD", tmp, false);
        free(tmp);
    }
    else
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

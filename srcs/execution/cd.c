/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:15:39 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/07 21:06:46 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_last_slash(char *str);

static int	special_case(t_data *data, char *tmp)
{
	if (data->check == 0)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 1);
		perror("getcwd");
		free(tmp);
		data->check++;
	}
	else if (access(tmp, X_OK) != -1)
	{
		chdir(tmp);
		export1(data, "PWD", tmp, false);
		export1(data, "OLDPWD", data->path, false);
		free(tmp);
		data->check = 0;
		return (0);
	}
	else
	{
		tmp = ft_substr_free1(tmp, 0, find_last_slash(tmp));
		special_case(data, tmp);
	}
	return (0);
}

static int	find_last_slash(char *str)
{
	int	i;
	int	last_slash;

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
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	if (!home_dir || home_dir[0] == '\0')
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (cwd == NULL)
	{
		perror("getcwd");
		return (1);
	}
	export1(data, "OLDPWD", cwd, false);
	if (chdir(home_dir) == -1)
	{
		perror(home_dir);
		return (1);
	}
	export1(data, "PWD", home_dir, false);
	return (0);
}

static int	change_to_directory(t_data *data, char *dir_path)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(data->path, PATH_MAX);
	tmp = ft_strdup(data->path);
	if ((!ft_strcmp(dir_path, "..")
			|| !ft_strcmp(dir_path, ".")) && cwd == NULL)
		return (special_case(data, tmp), free(cwd), 0);
	else if (cwd == NULL)
	{
		perror("getcwd");
		return (1);
	}
	if (chdir(dir_path) == -1)
	{
		perror(dir_path);
		g_exit_status = 1;
		return (1);
	}
	cwd = getcwd(NULL, PATH_MAX);
	export1(data, "OLDPWD", data->path, false);
	export1(data, "PWD", cwd, false);
	free(tmp);
	free(cwd);
	return (0);
}

void	ft_cd(t_data *data)
{
	char	*dir_path ;
	char	*home_dir;
	t_exec	*tmp;

	tmp = data->cmds;
	home_dir = ft_getenv(data, "HOME");
	if (!tmp->str[1] && ft_strcmp(tmp->str[0], "cd") == 0)
		g_exit_status = change_to_home_directory(data, home_dir);
	else
	{
		dir_path = tmp->str[1];
		change_to_directory(data, dir_path);
	}
}

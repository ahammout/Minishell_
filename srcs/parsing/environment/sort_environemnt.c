/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_environemnt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:58:36 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/31 15:59:15 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int find_eq(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (i);
        i++;
    }
    return (i);
}

static t_env   *strToList(char **envp)
{
    t_env *env;
    t_env *tmp;
    int i;
    char **tmp2;

    i = 0;
    env = NULL;
    while (envp[i])
    {
        tmp = (t_env *)malloc(sizeof(t_env));
        tmp->name = ft_substr(envp[i], 0, find_eq(envp[i]));
        if (find_eq(envp[i]) == ft_strlen(envp[i]))
            tmp->value = NULL;
        else
            tmp->value = ft_substr(envp[i],find_eq(envp[i]) + 1, ft_strlen(envp[i]) - find_eq(envp[i]));
        tmp->next = env;
        env = tmp;
        i++;
    }
    return (env);
}

static char **sort_env(char **envp)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    while (envp[i])
    {
        j = i + 1;
        while (envp[j])
        {
            if (ft_strcmp(envp[i], envp[j]) < 0)
            {
                tmp = envp[i];
                envp[i] = envp[j];
                envp[j] = tmp;
            }
            j++;
        }
        i++;
    }
    return (envp);
}

static char **list_to_str(t_env *env)
{
    char **envp;
    int i;
    t_env *tmp;
    char *tmp2;

    i = 0;
    tmp = env;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    envp = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    tmp = env;
    while (tmp)
    {
        if (tmp->value)
        {
            tmp2 = ft_strjoin(tmp->name, "=");
            envp[i] = ft_strjoin(tmp2, tmp->value);
            free(tmp2);
        }
        else
            envp[i] = ft_strdup(tmp->name);
        tmp = tmp->next;
        i++;
    }
    envp[i] = NULL;
    return (envp);
}

void printEnv(t_data *data)
{
    t_env *tmp;

    tmp = data->env;
    while (tmp)
    {
        if (tmp->value)
        {
            ft_putstr_fd(tmp->name, data->cmds->out_file); // is for test only to be replaced by cmds->out_file
            ft_putstr_fd("=", data->cmds->out_file); // is for test only to be replaced by cmds->out_file
            ft_putstr_fd(tmp->value, data->cmds->out_file); // is for test only to be replaced by cmds->out_file
            ft_putstr_fd("\n", data->cmds->out_file); // is for test only to be replaced by cmds->out_file
        }
        tmp = tmp->next;
    }
}

void    export0(t_data *data)
{
    t_env *tmp;

    tmp = sort_environment(data);
       while (tmp)
    {
        ft_putstr_fd("declare -x ", data->cmds->out_file); // is for test only to be replaced by cmds->out_file
        ft_putstr_fd(tmp->name, data->cmds->out_file); // is for test only to be replaced by cmds->out_file
        if (tmp->value)
        {
            ft_putstr_fd("=\"", data->cmds->out_file); // is for test only to be replaced by cmds->out_file
            ft_putstr_fd(tmp->value, data->cmds->out_file); // is for test only to be replaced by cmds->out_file
            ft_putstr_fd("\"",data->cmds->out_file); // is for test only to be replaced by cmds->out_file
        }
        ft_putstr_fd("\n", data->cmds->out_file); // is for test only to be replaced by cmds->out_file
        tmp = tmp->next;
    }
}

t_env   *sort_environment(t_data *data)
{
    char **envp;
    t_env *tmp;

    envp = list_to_str(data->env);
    envp = sort_env(envp);
    tmp = strToList(envp);
    free(envp);
    return (tmp);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:51:05 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/31 16:12:54 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void ft_free_tab(char ***tab)
{
    int i;

    i = 0;
    while ((*tab)[i])
    {
        free((*tab)[i]);
        i++;
    }
    free(*tab);
    *tab = NULL;
}

char **ft_tab_add_back(char **tab, char *str)
{
    int i;
    char **new_tab;

    i = 0;
    while (tab[i])
        i++;
    new_tab = malloc(sizeof(char *) * (i + 2));
    i = 0;
    while (tab[i])
    {
        new_tab[i] = ft_strdup(tab[i]);
        i++;
    }
    new_tab[i] = ft_strdup(str);
    new_tab[i + 1] = NULL;
    //ft_free_tab(&tab);
    return (new_tab);
}

void updt_shlvl(t_data *data)
{
    int i = 0;
    int lvl = 1;
    char *shlvl_str;

    while (data->envp_[i]) {
        if (!ft_strncmp(data->envp_[i], "SHLVL=", 6))
        {
            lvl = ft_atoi(data->envp_[i] + 6);
            lvl++;
            if (lvl > 1000)
            {
                lvl = 1;
                ft_putstr_fd("Warning: SHLVL is too high, resetting to 1", 2);
            }
            //free(data->envp_[i]);
            data->envp_[i] = ft_strjoin("SHLVL=", ft_itoa(lvl));
            break;
        }
        i++;
    }
    if (!data->envp_[i]) {
        shlvl_str = ft_strjoin("SHLVL=", ft_itoa(lvl));
        data->envp_ = ft_tab_add_back(data->envp_, shlvl_str);
        //free(shlvl_str);
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:51:05 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/03 04:58:52 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void check_warning(int *lvl)
{
    if (*lvl > 1000)
    {
        *lvl = 1;
        ft_putstr_fd("Warning: SHLVL is too high, resetting to 1\n", 2);
    }
}
void updt_shlvl(t_data *data)
{
    int lvl;
    t_env *tmp ;

    lvl = 1;
    tmp = data->env;
    while (tmp)
    {
        if (!ft_strncmp(tmp->name, "SHLVL", 5))
        {
            lvl = ft_atoi(tmp->value) + 1;
            check_warning(&lvl);
            free(tmp->value);
            tmp->value = ft_itoa(lvl);
            break;
        }
        tmp = tmp->next;
    }
    if (!tmp)
        export1(data, "SHLVL", "1", false);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:03:45 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/01 18:01:54 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    display_environment(t_data *data)
{
    t_env *head;
    int index;

    head = data->env;
    index = 0;
    while (head != NULL)
    {
        printf("---------------------  Node %d  ---------------------\n\n", index);
        printf(" *Name: %s\n", head->name);
        printf(" *Value: %s\n\n", head->value);
        index++;
        head = head->next;
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/04 17:02:49 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int exitS;

 void ee()
 {
     system("leaks minishell");
 }

int init_data(t_data *data)
{
    data->buffer = NULL;
    data->err = NULL;
    data->tokens = NULL;
    data->cmds = NULL;
    return (0);
}

void    read_line(t_data *data)
{
    int buffer_size;

    init_data(data);
    buffer_size = 0;
    while (!buffer_size)
    {
        data->buffer = readline("(minishell@Developers)$> ");
        if (!data->buffer)
        {
            exitS = 2;
            ft_putstr_fd("exit\n", 1);
            exit_minishell(data, NULL);
        }
        buffer_size = ft_strlen(data->buffer);
    }
}

int main(int ac, char **av, char **envp)
{
    t_data  data;
    
     atexit(ee);
    (void)**av;
    if (ac == 1)
    {
        data.envp_ = envp;
        set_environment(&data, envp);
        updt_shlvl(&data);
        while (1)
        {
            signals_handler();
            read_line(&data);
            add_history(data.buffer);
            data.cmds = parser(&data);
            /////// EXECUTION PART /////
            if (data.cmds)
               cmd_call(&data);
            
        }
    }
    //free_env_list(&data);
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/03 07:29:00 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int exitS;

 void ee()
 {
     system("leaks minishell");
 }

int main(int ac, char **av, char **envp)
{
    t_data  data;
    int     status;
    int     buffer_size;
    char    path[PATH_MAX];
    int     her_file = 0;

    atexit(ee);
    (void)**av;
    if (ac == 1)
    {
        data.envp_ = envp;
        data.buffer = NULL;
        set_environment(&data, envp);
        updt_shlvl(&data);
        while (1)
        {
            signals_handler();
            data.err = NULL;
            buffer_size = 0;
            while (!buffer_size)
            {
                data.buffer = readline("(minishell@Developers)$> ");
                if (!data.buffer)
                {
                    exitS = 2;
                    ft_putstr_fd("exit\n", 1);
                    exit_minishell(&data, NULL, 2);
                }
                buffer_size = ft_strlen(data.buffer);
            }
            add_history(data.buffer);
            data.cmds = parser(&data);
            /////// EXECUTION PART /////
            if (data.cmds)
               cmd_call(&data,her_file);
        }
    }
    //free_env_list(&data);
    return (0);
}

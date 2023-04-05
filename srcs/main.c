/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/05 04:02:42 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


//
int	exitS;

//  void ee()
//  {
//      system("leaks minishell");
//  }

int init_data(t_data *data)
{
    data->buffer = NULL;
    data->err = NULL;
    data->tokens = NULL;
    data->cmds = NULL;
    return (0);
}

void	read_line(t_data *data)
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

void	set_beta_env(t_data *data)
{
	data->envp_ = NULL;
	data->vars->path = ft_strdup(getenv("PATH"));
	data->vars->pwd = ft_strdup(getenv("PWD"));
	data->vars->pwd = ft_strdup(getenv("OLDPWD"));
	data->vars->shlvl = ft_strdup(getenv("SHLVL"));
}

int main(int ac, char **av, char **envp)
{
    t_data  data;
    
    //  atexit(ee);
    (void)**av;
    if (ac == 1)
    {
		if (envp[0])
			set_environment(&data, envp);
		else
		{
			data.env = NULL;
			set_env_beta(&data);
		}
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

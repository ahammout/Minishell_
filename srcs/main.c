/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/05 22:45:31 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


//
int	g_exit_status;

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
			g_exit_status = 2;
			ft_putstr_fd("exit\n", 1);
			exit_minishell(data, NULL);
		}
		buffer_size = ft_strlen(data->buffer);
    }
}

void	set_beta_env(t_data *data)
{
	data->env = (t_env *)malloc(sizeof(t_env));
	data->env->name = ft_strdup("PWD");
	data->env->value = getcwd(NULL, 0);
	data->env->next = (t_env *)malloc(sizeof(t_env));
	data->env->next->name = ft_strdup("OLDPWD");
	data->env->next->value = (char *)malloc(sizeof(char) * 1);
	data->env->next->value[0] = '\0';
	data->env->next->next = (t_env *)malloc(sizeof(t_env));
	data->env->next->next->name = ft_strdup("SHLVL");
	data->env->next->next->value = ft_strdup("0");
	data->env->next->next->next = (t_env *)malloc(sizeof(t_env));
	data->env->next->next->next->name = ft_strdup("PATH");
	data->env->next->next->next->value = ft_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	data->env->next->next->next->next = NULL;
}

int main(int ac, char **av, char **envp)
{
    t_data  data;
    
     //atexit(ee);
    (void)**av;
    if (ac == 1)
    {
		if (envp[0])
			set_environment(&data, envp);
		else
			set_beta_env(&data);
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

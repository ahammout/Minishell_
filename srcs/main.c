/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/08 03:23:51 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_exit_status ;
// void ee()
// {
// 	system("leaks minishell");
// }

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
	int	buffer_size;

	init_data(data);
	buffer_size = 0;
	while (!buffer_size)
	{
		data->buffer = readline("(minishell@Developers)$> ");
		printf("The buffer is: %s", data->buffer);
		if (!data->buffer)
		{
			g_exit_status = 2;
			ft_putstr_fd("exit\n", 1);
			exit_minishell(data, NULL);
		}
		buffer_size = ft_strlen(data->buffer);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	//atexit(ee);
	(void)**av;
	{
		set_environment(&data, envp);
		updt_shlvl(&data);
		while (1)
		{
			signals_handler();
			read_line(&data);
			add_history(data.buffer);
			data.cmds = parser(&data);
			if (data.cmds)
				cmd_call(&data);
			//display_cmds(data.cmds);
		}
	}
	return (0);
}

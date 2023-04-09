/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 03:29:45 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 17:54:00 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status ;

int	init_data(t_data *data)
{
	data->line = NULL;
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
		data->line = readline("(minishell@Developers)$> ");
		if (!data->line)
		{
			g_exit_status = 2;
			ft_putstr_fd("exit\n", 1);
			exit_minishell(data, NULL);
		}
		buffer_size = ft_strlen(data->line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)**av;
	set_environment(&data, envp);
	updt_shlvl(&data);
	while (1)
	{
		signals_handler();
		read_line(&data);
		add_history(data.line);
		data.cmds = parser(&data);
		if (data.cmds)
			cmd_call(&data);
	}
	return (0);
}

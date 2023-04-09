/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:17:53 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/09 15:02:33 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*save_std(void)
{
	int	*stds;

	stds = malloc(sizeof(int) * 2);
	stds[0] = dup(0);
	stds[1] = dup(1);
	return (stds);
}

void	close_fd(t_data	*data)
{
	int	i;

	i = -1;
	while (++i < data->pipex->p_c)
	{
		close(data->pipex->p_fd[i][0]);
		close(data->pipex->p_fd[i][1]);
	}
}

void	handle_loop(t_vars	pipe, t_data	*data)
{
	restore(pipe.std, 0, pipe.pids, data);
	pipe.status = pipes_redirection(pipe.tmp, pipe.i, data);
	pipe.pids[pipe.i] = fork();
	if (pipe.pids[pipe.i] == -1)
	{
		perror("fork");
		restore(pipe.std, 1, pipe.pids, data);
		g_exit_status = 1;
		return ;
	}
	if (pipe.pids[pipe.i])
		ignore_signal();
	pipe_exe(pipe.pids, data, pipe.tmp, pipe.i);
}

char	*ft_getenv(t_data *data, char *str)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, str) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_path(char *str, t_data *data, int *status)
{
	char	**paths;
	char	*path;
	int		i;

	path = ft_getenv(data, "PATH");
	paths = ft_split(path, ':');
	if (!paths)
		return (*status = 1, NULL);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free1(path, str);
		if (access(path, F_OK) == 0)
			return (free_array(paths), path);
		free(path);
	}
	return (*status = 127, free_array(paths), NULL);
}

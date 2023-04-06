/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:17:53 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/05 16:09:34 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_free1(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	count_pps(t_exec	*exec)
{
	int		cnt;
	t_exec	*tmp;

	cnt = 0;
	tmp = exec;
	while (tmp)
	{
		if (tmp->next)
			cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}

int	**pipe_gener(int count)
{
	int	**pipes;
	int	i;

	i = -1;
	pipes = malloc(sizeof(int *) * count);
	if (!pipes)
		return (0);
	while (++i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
	}
	return (pipes);
}

void	red_inp(t_exec	*tmp, int status, t_data	*data, int i)
{
	if (tmp->in_file != 0)
	{
		if (i != 0)
			dup2(tmp->in_file, data->pipex->p_fd[i - 1][0]);
		else
			dup2(tmp->in_file, 0);
	}
	return (status = 0, (void)0) ;
}

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

void	handle_loop(t_vars	pipe, t_data	*data, char **envp)
{
	restore_parent(pipe.std, 0, pipe.pids, data);
	pipe.status = pipes_redirection(pipe.tmp, pipe.i, data);
	if (pipe.status == -1)
		return ;
	pipe.pids[pipe.i] = fork();
	if (pipe.pids[pipe.i] == -1)
	{
		perror("fork");
		restore_parent(pipe.std, 1, pipe.pids, data);
		exitS = 1;
		return ;
	}
	if (pipe.pids[pipe.i])
		ignore_signal();
	pipe_exe(pipe.pids, data, pipe.tmp, pipe.i, envp);
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

	path = ft_getenv(data,"PATH");
	if (!path)
		return (*status = 127, NULL);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:06:39 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/09 21:47:40 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restore(int *stds, int status, int *pids, t_data *data)
{
	int	i;

	dup2(stds[0], 0);
	dup2(stds[1], 1);
	if (status == 1)
	{
		i = -1;
		close_fds(data);
		while (++i <= data->pipex->p_c)
		{
			waitpid(pids[i], &status, 0);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
				{
					ft_putstr_fd("\n", 1);
					g_exit_status = 128 + WTERMSIG(status);
				}
			}
		}
		signals_handler();
	}
}

void	pipe_exe(int *pids, t_data *data, t_exec *tmp, int i)
{
	int		status;
	char	*path;
	char	**envp;

	path = NULL;
	envp = NULL;
	if (pids[i] == 0)
	{
		signals_handler();
		handle_fds(data, i);
		if (tmp->in_file == -1)
			error_display(tmp);
		else if (!tmp->str ||!builtin(data, tmp))
			;
		else if (tmp->str[0] && tmp->str[0][0] == '\0')
			is_empty(data, tmp);
		else
		{
			path = get_path(tmp->str[0], data, &status);
			envp = list_to_str(data->env);
			file_checker(path, data, tmp, envp);
		}
		exit(g_exit_status);
	}
}

static void	init_pipes(t_data *data, t_exec *tmp, t_vars *pipe)
{
	pipe->i = 0;
	pipe->status = 1;
	pipe->tmp = tmp;
	pipe->pids = malloc(sizeof(int) * (data->pipex->p_c + 1));
	pipe->std = save_std();
}

void	free_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipex->p_c)
	{
		free(data->pipex->p_fd[i]);
		i++;
	}
	free(data->pipex->p_fd);
	free(data->pipex);
}

void	exec_pipes(t_exec *exc, t_data *data)
{
	t_vars	pipe;

	init_pipes(data, exc, &pipe);
	if (data->pipex->p_c)
		data->pipex->p_fd = pipe_gener(data->pipex->p_c);
	while (pipe.i <= data->pipex->p_c && pipe.tmp)
	{
		handle_loop(pipe, data);
		pipe.tmp = pipe.tmp->next;
		pipe.i++;
	}
	restore(pipe.std, 1, pipe.pids, data);
	free(pipe.std);
	free(pipe.pids);
	free_pipes(data);
	free_cmds_list(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:45:32 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/09 15:12:53 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mini_execve(char *path, t_exec *tmp, char **envp, int i)
{
	if (i == 0)
	{
		if (execve(path, tmp->str, envp) == -1)
		{
			g_exit_status = 127;
			perror("Minishell ");
		}
	}
	else
	{
		if (execve(tmp->str[0], tmp->str, envp) == -1)
		{
			if (errno == ETXTBSY)
			{
				perror("Minishell");
				g_exit_status = 126;
			}
			else
				check_bash(tmp->str[0], tmp, envp);
		}
	}
}

void	file_checker(char *path, t_data *data, t_exec *tmp, char **envp)
{
	int	st;

	st = check_file(tmp->str[0]);
	if (path && ft_strncmp(tmp->str[0], "./", 2))
		return (mini_execve(path, tmp, envp, 0), (void)0);
	else if (st == 1 && ft_strncmp(tmp->str[0], "./", 2) == 0)
		return (is_directory(data, tmp), free(path), (void)0);
	else if (st == 2 && ft_strncmp(tmp->str[0], "./", 2) == 0)
		return (is_perms(data, tmp), free(path), (void)0);
	else if (st == 3)
		return (mini_execve(path, tmp, envp, 1), (void)0);
	else if (st == 4 && ft_strncmp(tmp->str[0], "./", 2) == 0)
		return (is_no_such_file(data, tmp), free(path), (void)0);
	else
		return (is_no_cmd(data, tmp), free(path), (void)0);
}

int	pipes_redirection(t_exec *tmp, int i, t_data *data)
{
	int	status;

	status = 0;
	if (tmp)
	{
		if (tmp->in_file == -1)
			return (-1);
		red_inp(tmp, status, data, i);
		if (tmp->out_file != 1)
		{
			if (i != data->pipex->p_c)
				dup2(tmp->out_file, data->pipex->p_fd[i][1]);
			else
				dup2(tmp->out_file, 1);
		}
	}
	return (0);
}

void	close_fds(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->pipex->p_c)
	{
		close(data->pipex->p_fd[i][0]);
		close(data->pipex->p_fd[i][1]);
	}
}

void	handle_fds(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < data->pipex->p_c)
	{
		if (j + 1 != i || i == 0)
			close(data->pipex->p_fd[j][0]);
		if (i == data->pipex->p_c || i != j)
			close(data->pipex->p_fd[j][1]);
		j++;
	}
	if (i != 0)
	{
		dup2(data->pipex->p_fd[i - 1][0], 0);
		close(data->pipex->p_fd[i - 1][0]);
	}
	if (i != data->pipex->p_c)
	{
		dup2(data->pipex->p_fd[i][1], 1);
		close(data->pipex->p_fd[i][1]);
	}
}

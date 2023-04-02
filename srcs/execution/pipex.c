/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:06:39 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/02 22:29:37 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void file_checker(char *path, t_data *data, t_exec *tmp)
{
	int st;

	st = check_file(tmp->str[0]);
    if (path)
    {
        if (execve(path,tmp->str, data->envp_) == -1)
            {
                exitS = 127;
                perror("Minishell ");
            }
    }
	else if (st == 1)
		return (is_directory(data), free(path), (void)0);
	else if (st == 2)
		return (is_perms(data), free(path), (void)0);
	else if (st == 3)
		{
            if (execve(tmp->str[0],tmp->str, data->envp_) == -1)
            {
                exitS = 127;
                perror("Minishell ");
            }
        }
	else if (st == 4)
		return (is_no_such_file(data), free(path), (void)0);
    else    
        return (is_no_cmd(data), free(path), (void)0);
}

int pipes_redirection(t_exec *tmp, int file_, int i, t_data *data)
{
    int         status;

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

void	close_fds(t_data	*data)
{
	int	i;

	i = -1;
	while (++i < data->pipex->p_c)
	{
		close(data->pipex->p_fd[i][0]);
		close(data->pipex->p_fd[i][1]);
	}
}

void handle_fds(t_data *data, int i) {
    int j = 0;

    while (j < data->pipex->p_c) {
        if (j + 1 != i || i == 0) {
            close(data->pipex->p_fd[j][0]); // Close read end
        }
        if (i == data->pipex->p_c || i != j) {
            close(data->pipex->p_fd[j][1]); // Close write end
        }
        j++;
    }

    if (i != 0) {
        dup2(data->pipex->p_fd[i - 1][0], 0); // Duplicate read end of previous process's pipe
        close(data->pipex->p_fd[i - 1][0]); // Close original read end fd
    }

    if (i != data->pipex->p_c) {
        dup2(data->pipex->p_fd[i][1], 1); // Duplicate write end of current process's pipe
        close(data->pipex->p_fd[i][1]); // Close original write end fd
    }
}


void    restore_parent(int  *stds, int status, int  *pids, t_data   *data)
{
    int     i;

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
                exitS = WEXITSTATUS(status);
            if (WIFSIGNALED(status))
            {
                if (WTERMSIG(status) == SIGINT)
                {
                    ft_putstr_fd("\n", 1);
                    exitS = 128 + WTERMSIG(status);
                }
            }
        }
        signals_handler();
    }
}

void    pipe_exe(int *pids, t_data  *data, t_exec *tmp, int i)
{
    int status;
    char *path;

    if (pids[i] == 0)
    {
        handle_fds(data, i);
        if (!builtin(data, tmp))
            ;
        else
        {
              path = get_path(tmp->str[0], data, &status);
              file_checker(path, data, tmp);    
        }
        exit(exitS);
    }
}

 static void init_pipes(t_data *data, t_exec *tmp,t_vars *pipe)
{
    pipe->i = 0;
    pipe->status = 1;
    pipe->tmp = tmp;
    pipe->pids = malloc(sizeof(int) * (data->pipex->p_c + 1));
    pipe->std = save_std();
}
void    exec_pipes(t_exec *exc, t_data *data, int file_, char **envp_)
{
    t_vars  pipe;
    int i;

    i = 0;
    init_pipes(data, exc, &pipe);
    if (data->pipex->p_c)
        data->pipex->p_fd = pipe_gener(data->pipex->p_c);
    while (pipe.i <= data->pipex->p_c && pipe.tmp)
    {
        handle_loop(pipe, file_, data);
        pipe.tmp = pipe.tmp->next;
        pipe.i++;
    }
    restore_parent(pipe.std, 1, pipe.pids, data);
    free(pipe.std);
    free(pipe.pids);
    if (data->pipex->p_fd[0])
    {
        while (i < data->pipex->p_c)
        {
            free(data->pipex->p_fd[i]);
            i++;
        }
        free(data->pipex->p_fd);
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:16:09 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/05 09:23:41 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_exit_status(int status)
{
	if (WIFEXITED(status))
		exitS = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		ft_putstr_fd("\n", 1);
		exitS = 128 + WTERMSIG(status);
	}
}

void	redirect_file_descriptors(int in_file, int out_file)
{
	if (in_file != STDIN_FILENO)
		dup2(in_file, STDIN_FILENO);
	if (out_file != STDOUT_FILENO)
		dup2(out_file, STDOUT_FILENO);
}

void	save_file_descriptors(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

void	exec_command(int pid, t_exec *exc, char *path, char **envp)
{
	if (pid == 0)
	{
		if (exc->in_file != STDIN_FILENO)
			close(exc->in_file);
		if (exc->out_file != STDOUT_FILENO)
			close(exc->out_file);
		if (execve(path, exc->str, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
}

void	execute_command(t_exec *exec, char *path, char **envp)
{
	int		status;
	int		saved_stdin;
	int		saved_stdout;
	t_pid		pid;

	save_file_descriptors(&saved_stdin, &saved_stdout);
	redirect_file_descriptors(exec->in_file, exec->out_file);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid)
		ignore_signal();
	exec_command(pid, exec, path, envp);
	waitpid(pid, &status, 0);
	handle_exit_status(status);
	signals_handler();
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

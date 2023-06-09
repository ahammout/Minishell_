/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:49:05 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 21:45:33 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	heredoc_action(t_data *data, int status, int fd[2])
{
	if (status == 0)
	{
		g_exit_status = 0;
		close(fd[1]);
		data->cmds->in_file = fd[0];
		data->tokens->type = EMPTY;
		data->tokens->next->type = EMPTY;
		data->tokens = data->tokens->next->next;
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		return (0);
	}
	return (1);
}

void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_exit_status = 1;
		exit(g_exit_status);
	}
}

void	read_input(t_data *data, int fd[2])
{
	char	*buffer;

	close(fd[0]);
	signal(SIGINT, heredoc_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		buffer = readline("heredoc> ");
		if (!buffer)
			exit(130);
		if (ft_strcmp(buffer, data->tokens->next->lex) == 0)
		{
			free(buffer);
			break ;
		}
		ft_putstr_fd(buffer, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(buffer);
	}
	close(fd[1]);
	exit(0);
}

int	heredoc_handler(t_data *data)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(fd) == -1)
		exit_minishell(data, "Minishell: pipe() failed.");
	pid = fork();
	if (pid == -1)
		exit_minishell(data, "Minishell: fork() failed.");
	if (pid == 0)
		read_input(data, fd);
	waitpid(pid, &status, 0);
	if (!heredoc_action(data, status, fd))
		return (0);
	return (1);
}

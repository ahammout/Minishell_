/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:46:44 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/05 17:25:32 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ignore_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	signals_router(int signal, siginfo_t *siginfo, void *content)
{
	content = NULL;
	siginfo = NULL;
	if (signal == SIGINT)
	{
		exitS = 130;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals_handler(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signals_router;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:21:39 by pdolinar          #+#    #+#             */
/*   Updated: 2022/10/24 13:37:05 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 1;
	}
}

static
void	sig_handler_exec(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_exit_code = 130;
	}
	if (signum == SIGQUIT)
	{
		write(1, "\b\b", 2);
		write(1, "^\\Quit\n", 7);
		g_exit_code = 131;
	}
}

static
void	sig_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		g_exit_code = 1;
	}
}

void	handle_signal(int i)
{
	struct sigaction	new_action;

	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	rl_catch_signals = 0;
	if (i == 1)
		new_action.sa_handler = &sig_handler_heredoc;
	else if (i == 2)
		new_action.sa_handler = &sig_handler_exec;
	else
		new_action.sa_handler = &sig_handler;
	sigaction(SIGINT, &new_action, NULL);
	sigaction(SIGQUIT, &new_action, NULL);
	sigaction(SIGPIPE, &new_action, NULL);
}

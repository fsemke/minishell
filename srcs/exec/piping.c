/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:05:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/10/26 11:26:54 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* start pipe process */
static
void	pipe_process(int *pipefd, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(&pipefd[i]) == -1)
		{
			write(2, "Failed to pipe\n", 16);
			exit(EXIT_FAILURE);
		}
		i += 2;
	}
}

static
void	set_pipefd(t_exec *cmd, int *pipefd, int j)
{
	t_redir	*redir;

	redir = cmd->data->redir;
	ft_redir(cmd, redir->filefd);
	if (j != 0)
		dup2(pipefd[(j - 1) * 2], STDIN_FILENO);
	if (redir->flag[0] == 0)
	{	
		dup2(redir->filefd[0], STDIN_FILENO);
		close(redir->filefd[0]);
	}
	if (cmd->next)
		dup2(pipefd[j * 2 + 1], STDOUT_FILENO);
	if (redir->flag[1] == 1)
	{
		dup2(redir->filefd[1], STDOUT_FILENO);
		close(redir->filefd[1]);
	}
}

void	ft_pipe(t_exec *cmd, int num_pipes, int *pipefd)
{
	t_exec	*head;
	int		j;

	head = cmd;
	pipe_process(pipefd, num_pipes);
	j = 0;
	while (cmd)
	{
		cmd->pid = fork();
		fd_pid_error(0, cmd->pid);
		if (cmd->pid == 0)
		{
			set_pipefd(cmd, pipefd, j);
			child_process(cmd, pipefd, num_pipes);
		}
		cmd = cmd->next;
		j++;
	}
	parent_process(head, pipefd, num_pipes);
}

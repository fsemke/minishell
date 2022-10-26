/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:37:14 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/26 11:39:11 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	change_std(t_redir	*redir)
{
	if (redir->flag[0] == 0)
	{
		dup2(redir->filefd[0], STDIN_FILENO);
		close (redir->filefd[0]);
	}
	if (redir->flag[1] == 1)
	{
		dup2(redir->filefd[1], STDOUT_FILENO);
		close (redir->filefd[1]);
	}
}

int	single_process(t_exec *cmd)
{
	t_redir	*redir;
	int		status;

	redir = cmd->data->redir;
	ft_redir(cmd, redir->filefd);
	if (g_exit_code != 0)
		return (0);
	change_std(redir);
	status = 0;
	if (cmd->builtin > 0)
		return (return_builtin(cmd->builtin, cmd));
	else
	{
		cmd->pid = fork();
		fd_pid_error(0, cmd->pid);
		if (cmd->pid == 0)
			ft_new_process(cmd);
		waitpid(cmd->pid, &status, 0);
	}
	if (g_exit_code == 0)
		g_exit_code = WEXITSTATUS(status);
	return (0);
}

void	ft_new_process(t_exec *cmd)
{
	t_redir	*redir;

	redir = cmd->data->redir;
	close(redir->saved_stdout);
	close(redir->saved_stdin);
	if (cmd->path == NULL)
		error_path(cmd->cmd->token, cmd->data->env);
	if (execve(cmd->path, cmd->options, cmd->data->envp) == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
}

void	child_process(t_exec *cmd, int *pipefd, int num_pipes)
{
	t_redir	*redir;
	int		i;

	redir = cmd->data->redir;
	close(redir->saved_stdout);
	close(redir->saved_stdin);
	i = 0;
	while (i < num_pipes)
		close(pipefd[i++]);
	if (cmd->builtin == 0)
		ft_new_process(cmd);
	return_builtin(cmd->builtin, cmd);
	exit(EXIT_SUCCESS);
}

void	parent_process(t_exec *head, int *pipefd, int num_pipes)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < num_pipes)
		close(pipefd[i++]);
	while (head)
	{
		waitpid(head->pid, &status, 0);
		head = head->next;
	}
	if (g_exit_code == 0)
		g_exit_code = WEXITSTATUS(status);
}

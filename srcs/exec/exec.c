/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:41:57 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/26 11:44:53 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	std_inout(t_data *data)
{
	t_redir	*redir;

	redir = data->redir;
	redir->flag[0] = -1;
	redir->flag[1] = -1;
	redir->saved_stdin = dup(STDIN_FILENO);
	redir->saved_stdout = dup(STDOUT_FILENO);
}

static
void	restore_stdinout(t_data *data)
{
	t_redir	*redir;
	int		count_fds;
	char	*tmp_name;

	redir = data->redir;
	if (redir->flag[0] == 0)
		close(redir->filefd[0]);
	if (redir->flag[1] == 1)
		close(redir->filefd[1]);
	dup2(redir->saved_stdout, STDOUT_FILENO);
	dup2(redir->saved_stdin, STDIN_FILENO);
	close(redir->saved_stdout);
	close(redir->saved_stdin);
	count_fds = count_type(data->tokens, HEREDOC);
	while (count_fds--)
	{
		tmp_name = ft_itoa(count_fds);
		unlink(tmp_name);
		free(tmp_name);
	}
	free(data->here_fds);
}

int	ft_exec(t_exec *cmd)
{
	t_data	*data;
	int		*pipefd;
	int		exit_status;
	int		num_pipes;

	exit_status = 0;
	if (!cmd)
		return (0);
	data = cmd->data;
	std_inout(data);
	handle_signal(2);
	num_pipes = (cmd->data->num_cmds - 1) * 2;
	if (num_pipes)
	{
		pipefd = malloc(sizeof(int) * num_pipes);
		if (pipefd == NULL)
			return (EXIT_SHELL);
		ft_pipe(cmd, num_pipes, pipefd);
		free(pipefd);
	}
	else
		exit_status = single_process(cmd);
	restore_stdinout(data);
	handle_signal(0);
	return (exit_status);
}

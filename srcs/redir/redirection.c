/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:05:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/10/25 16:48:18 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	return_inputfd(t_token *node, t_token *next, t_exec *cmd)
{
	t_redir	*redir;
	char	*tmp_name;

	redir = cmd->data->redir;
	if (node->type == INPUT)
	{
		redir->filefd[0] = open(next->token, O_RDONLY, 0644);
		redir->flag[0] = 0;
	}
	else if (node->type == HEREDOC)
	{
		tmp_name = ft_itoa(cmd->heredoc_fdindex);
		redir->filefd[0] = open(tmp_name, O_RDONLY, 0644);
		free(tmp_name);
		redir->flag[0] = 0;
	}
}

static
void	return_outputfd(t_token *node, t_token *next, t_data *data)
{
	t_redir	*redir;

	redir = data->redir;
	if (node->type == OUTPUT)
	{
		redir->filefd[1] = open(next->token, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
		redir->flag[1] = 1;
	}
	else if (node->type == APPEND)
	{
		redir->filefd[1] = open(next->token, \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
		redir->flag[1] = 1;
	}
}

void	ft_redir(t_exec *cmd, int *filefd)
{
	t_token	*node;
	t_token	*next;

	node = cmd->cmd;
	while (node->previous && node->previous->type != PIPE)
		node = node->previous;
	next = node->next;
	while (node && node->type != PIPE)
	{
		return_inputfd(node, next, cmd);
		return_outputfd(node, next, cmd->data);
		if (node && (node->type == OUTPUT || node->type == APPEND)
			&& next && next->next
			&& (next->next->type == OUTPUT || next->next->type == APPEND))
			close(filefd[STDOUT_FILENO]);
		else if (node && (node->type == INPUT || node->type == HEREDOC)
			&& next && next->next
			&& (next->next->type == INPUT || next->next->type == HEREDOC))
			close(filefd[STDIN_FILENO]);
		node = next;
		if (next)
			next = next->next;
	}
}

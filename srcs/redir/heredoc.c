/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:34:41 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/25 21:01:02 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	heredoc_errorcheck(char **line, int *filefd, int i, char *delimiter)
{
	if (g_exit_code != 1)
		*line = readline("heredoc> ");
	if (g_exit_code == 1)
	{
		free(*line);
		close (*filefd);
		*filefd = open(ft_itoa(i), O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	if (*line == NULL || g_exit_code == 1)
		return (1);
	if (ft_strncmp(delimiter, *line, ft_strlen(delimiter)) == 0
		&& ft_strlen(delimiter) == ft_strlen(*line))
	{
		free(*line);
		return (1);
	}
	return (0);
}

/* return fd for heredoc */
static
int	heredoc(char *delimiter, int i)
{
	int		filefd;
	char	*line;
	char	*tmp_name;

	line = NULL;
	tmp_name = ft_itoa(i);
	filefd = open(tmp_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	fd_pid_error(filefd, 0);
	handle_signal(1);
	while (1)
	{
		if (heredoc_errorcheck(&line, &filefd, i, delimiter) == 1)
			break ;
		write(filefd, line, ft_strlen(line));
		write(filefd, "\n", 1);
		free(line);
	}
	free(tmp_name);
	handle_signal(0);
	return (filefd);
}

/* verify tokens for multiple heredoc */
static
void	set_heredoc_fd(t_data *data)
{
	t_token	*node;
	t_exec	*cmd;
	t_token	*next;
	int		heredoc_count;

	cmd = data->cmd;
	heredoc_count = -1;
	while (cmd)
	{
		node = cmd->cmd;
		while (node->previous && node->previous->type != PIPE)
			node = node->previous;
		next = node->next;
		while (node && node->type != PIPE)
		{
			if (node->type == HEREDOC)
				cmd->heredoc_fdindex = ++heredoc_count;
			node = next;
			if (next)
				next = next->next;
		}
		cmd = cmd->next;
	}
}

void	run_heredoc(t_data *data)
{
	t_token	*token;
	int		heredoc_num;
	int		i;

	token = data->tokens;
	heredoc_num = count_type(token, HEREDOC);
	data->here_fds = malloc(sizeof(int) * (heredoc_num + 1));
	i = 0;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			data->here_fds[i] = heredoc(token->next->token, i);
			close(data->here_fds[i]);
			i++;
		}
		token = token->next;
	}
	set_heredoc_fd(data);
}

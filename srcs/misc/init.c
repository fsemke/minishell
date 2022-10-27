/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:05:07 by pdolinar          #+#    #+#             */
/*   Updated: 2022/10/27 13:35:03 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_env(char **envp, t_data *data)
{
	int	i;

	data->env = NULL;
	i = 0;
	while (envp[i])
	{
		if (linking_nodes(envp[i], &data->env) == 1)
			return ;
		i++;
	}
	data->envp = envp;
	data->redir = malloc(sizeof(*data->redir));
}

void	init_exec(t_data *data)
{
	int	i;

	data->cmd = NULL;
	i = 0;
	while (i < data->num_cmds)
	{
		if (cmd_link_nodes(&data->cmd, data) == 1)
			return ;
		i++;
	}
}

void	ini_data(t_data *data)
{
	data->next_is_file = 0;
	data->cmd_found = 0;
	data->search_it = NULL;
	data->num_cmds = 0;
	data->tokens = NULL;
	data->here_fds = NULL;
}

/* create and fill the token node */
t_token	*ini_token(char *tmp, int type)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (token == NULL)
		return (NULL);
	token->token = tmp;
	token->type = type;
	token->next = NULL;
	token->previous = NULL;
	return (token);
}

char	**alloc_options(t_token *head)
{
	t_token	*to;
	char	**ptr;
	int		i;
	int		args_num;

	args_num = num_args_until_pipe(head);
	to = head;
	ptr = malloc(sizeof(char *) * (args_num + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < args_num)
	{
		if (to->type == EXEC || to->type == FLAG || to->type == ARG)
		{
			ptr[i] = ft_strdup(to->token);
			i++;
		}
		to = to->next;
	}
	ptr[i] = NULL;
	return (ptr);
}

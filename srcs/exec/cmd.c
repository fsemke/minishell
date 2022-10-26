/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:41:57 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/24 14:01:18 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	cmd_add_node(t_exec **head, t_exec *new)
{
	t_exec	*tmp;

	if (new == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static
t_token	*search_cmds(t_data *data)
{
	static int		first = 0;

	if (first == 0 || !data->search_it)
		data->search_it = data->tokens;
	first = 1;
	while (data->search_it->type != BUILTIN
		&& data->search_it->type != EXEC)
		data->search_it = data->search_it->next;
	if (data->search_it->next)
	{
		data->search_it = data->search_it->next;
		return (data->search_it->previous);
	}
	return (data->search_it);
}

static
t_exec	*cmd_init_node(t_data *data)
{
	t_exec	*node;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	node->cmd = search_cmds(data);
	node->builtin = return_type_builtin(node->cmd->token);
	node->path = NULL;
	node->heredoc_fdindex = -1;
	if (node->cmd->type == EXEC)
	{
		node->builtin = 0;
		node->path = parse_path(data->env, node->cmd->token);
	}
	node->options = alloc_options(node->cmd);
	node->data = data;
	node->next = NULL;
	return (node);
}

int	cmd_link_nodes(t_exec **head, t_data *data)
{
	t_exec	*node;

	node = cmd_init_node(data);
	if (node == NULL)
		return (1);
	cmd_add_node(head, node);
	return (0);
}

int	num_args_until_pipe(t_token *head)
{
	int	count;

	count = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == EXEC || head->type == FLAG || head->type == ARG)
			count++;
		head = head->next;
	}
	return (count);
}

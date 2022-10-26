/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:48:31 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/25 22:10:37 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_tokens(t_data *data)
{
	t_token	*tmp;
	t_token	*remove;

	tmp = data->tokens;
	if (tmp == NULL)
		return ;
	remove = tmp;
	while (tmp)
	{
		tmp = tmp->next;
		free(remove->token);
		free(remove);
		remove = tmp;
	}
	data->tokens = NULL;
}

void	cleanup_exec(t_data *data)
{
	t_exec	*exec;
	t_exec	*tmp_last;

	if (data->cmd)
	{
		exec = data->cmd;
		while (exec)
		{
			if (exec->options)
				free_double_p(exec->options);
			if (exec->path)
				free (exec->path);
			tmp_last = exec;
			exec = exec->next;
			free (tmp_last);
		}
	}
	data->cmd = NULL;
	data->search_it = NULL;
	free((char *)data->input);
	data->input = NULL;
}

/* free allocated memory */
void	free_double_p(char **local_paths)
{
	int	i;

	i = 0;
	while (local_paths[i] != NULL)
		free(local_paths[i++]);
	free(local_paths[i]);
	free(local_paths);
}

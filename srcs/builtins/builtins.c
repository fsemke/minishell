/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:03:43 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/26 12:37:14 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	buffer[1024];

	getcwd(buffer, 1024);
	printf("%s\n", buffer);
	return (0);
}

void	env(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}

void	echo(t_exec *exec)
{
	t_token	*i;
	int		newline;

	i = exec->cmd->next;
	newline = 1;
	if (i && i->type == FLAG && ft_strlen(i->token) == 2
		&& ft_strncmp(i->token, "-n", 2) == 0)
	{
		newline = 0;
		i = i->next;
	}
	while (i && i->type != PIPE)
	{
		if (i->type == ARG || i->type == FLAG)
		{
			printf("%s", i->token);
			if (i->next && i->next->type != PIPE)
				printf(" ");
		}
		i = i->next;
	}
	if (newline == 1)
		printf("\n");
}

void	unset(t_env *ptr, t_exec *exec)
{
	t_env	*tmp;
	char	*var;

	if (exec->cmd->next && exec->cmd->next->type == ARG)
		var = exec->cmd->next->token;
	else
		return ;
	if (ptr == NULL)
		return ;
	tmp = ptr;
	while (tmp)
	{
		if (strenv_cmp(var, tmp->var) == 0)
		{
			remove_node(&ptr, tmp);
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

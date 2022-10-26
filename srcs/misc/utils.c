/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:05:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/10/25 22:14:29 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_node(t_env **head, t_env *remove)
{
	t_env	*tmp;

	if (remove == *head)
		*head = remove->next;
	else
	{
		tmp = *head;
		while (tmp && tmp->next != remove)
			tmp = tmp->next;
		tmp->next = remove->next;
		remove->next = NULL;
	}
	free(remove->var);
	free(remove);
}

void	add_node(t_env **head, t_env *new)
{
	t_env	*tmp;

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

t_env	*init_node(char *str)
{
	t_env	*node;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	node->var = ft_strdup(str);
	node->next = NULL;
	return (node);
}

int	linking_nodes(char *str, t_env **head)
{
	t_env	*node;

	node = init_node(str);
	if (node == NULL)
		return (1);
	add_node(head, node);
	return (0);
}

void	clear_nodes(t_env **head)
{
	t_env	*tmp;
	t_env	*remove;

	tmp = *head;
	if (tmp == NULL)
		return ;
	remove = tmp;
	while (tmp)
	{
		tmp = tmp->next;
		free(remove->var);
		free(remove);
		remove = tmp;
	}
}

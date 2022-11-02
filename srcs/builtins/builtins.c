/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:03:43 by fsemke            #+#    #+#             */
/*   Updated: 2022/11/02 10:45:32 by fsemke           ###   ########.fr       */
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

	if (!head)
		return ;
	tmp = head;
	while (tmp)
	{
		if (ft_memchr(tmp->var, '=', ft_strlen(tmp->var)) != NULL)
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

void	unset(t_data *data, t_exec *exec)
{
	t_env	*tmp;
	char	*var;

	if (exec->cmd->next && exec->cmd->next->type == ARG)
		var = exec->cmd->next->token;
	else
		return ;
	if (data->env == NULL)
		return ;
	tmp = data->env;
	while (tmp)
	{
		if (strenv_cmp(var, tmp->var) == 0)
		{
			remove_node(data, tmp);
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

int	strenv_cmp(const char *str1, const char *str2)
{
	unsigned char		*s1;
	unsigned char		*s2;
	size_t				i;
	char				tmp_s1;
	char				tmp_s2;

	if (!str1)
		return ((int)str2[0]);
	i = 0;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	if (s1 == NULL)
		return (s2[0]);
	while (s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=' && (s1[i] || s2[i]))
		i++;
	if (s1[i] == '=')
		tmp_s1 = 0;
	else
		tmp_s1 = s1[i];
	if (s2[i] == '=')
		tmp_s2 = 0;
	else
		tmp_s2 = s2[i];
	return (tmp_s1 - tmp_s2);
}

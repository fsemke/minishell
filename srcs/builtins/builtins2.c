/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:51:23 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/27 11:17:49 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	chdir_to_home(t_token *token, t_env *iterator)
{
	if (!token || token->type == PIPE)
	{
		while (iterator && strenv_cmp(iterator->var, "HOME") != 0)
			iterator = iterator->next;
		if (!iterator)
		{
			write(2, "cd: HOME not set\n", 17);
			g_exit_code = 1;
		}
		else if (strenv_cmp(iterator->var, "HOME") == 0)
		{
			if (chdir(ft_strchr(iterator->var, '=') + 1))
			{
				write(2, "cd: HOME not set\n", 17);
				g_exit_code = 1;
			}
		}
	}
}

void	cd(t_exec *exec)
{
	t_token	*token;
	char	buffer[1024];
	char	old_path[1024];
	char	*tmp;
	char	*var;

	getcwd(old_path, 1024);
	var = ft_strjoin("OLDPWD=", old_path);
	export(exec->data->env, var);
	token = exec->cmd->next;
	if (!token || token->type == PIPE)
		chdir_to_home(token, exec->data->env);
	else if (token->next && token->next->type != PIPE)
		g_exit_code = ft_error("string not in pwd\n");
	else if (chdir(token->token) != 0)
		g_exit_code = ft_error("No such file or director\n");
	getcwd(buffer, 1024);
	tmp = ft_strjoin("PWD=", buffer);
	export(exec->data->env, tmp);
	free (tmp);
	free (var);
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

static
int	ft_is_str_digit(char *s)
{
	int	i;
	int	length;
	int	result;

	if (!s)
		return (0);
	i = -1;
	length = ft_strlen(s);
	while (++i < length)
	{
		result = ft_isdigit(s[i]);
		if (result == 0)
			return (0);
	}
	return (1);
}

int	ft_exit(t_exec *exec)
{
	if (exec->cmd->next && exec->cmd->next->type == ARG
		&& ft_is_str_digit(exec->cmd->next->token) == 0)
	{
		write (2, "exit: ", 6);
		write (2, exec->cmd->next->token, ft_strlen(exec->cmd->next->token));
		write (2, ": numeric argument required\n", 28);
		g_exit_code = 255;
	}
	else if (exec->cmd->next && exec->cmd->next->type == ARG
		&& exec->cmd->next->next && exec->cmd->next->next->type == ARG)
	{
		write (2, "exit: too many arguments\n", 25);
		g_exit_code = 1;
		return (1);
	}
	else if (exec->cmd->next && exec->cmd->next->type == ARG)
		g_exit_code = ft_atoi(exec->cmd->next->token);
	printf("exit\n");
	return (EXIT_SHELL);
}

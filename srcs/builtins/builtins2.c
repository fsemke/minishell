/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:51:23 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/27 14:42:07 by fsemke           ###   ########.fr       */
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

static
int	search_dir(t_exec *exec, t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == ARG)
		{
			if (chdir(token->token) == -1)
			{
				g_exit_code = ft_error("No such file or directory\n");
				return (1);
			}
			return (0);
		}
		token = token->next;
	}
	chdir_to_home(token, exec->data->env);
	return (0);
}

void	cd(t_exec *exec)
{
	char	buffer[1024];
	char	old_path[1024];
	char	*tmp;
	char	*var;

	getcwd(old_path, 1024);
	var = ft_strjoin("OLDPWD=", old_path);
	if (search_dir(exec, exec->cmd->next) == 1)
	{
		free (var);
		return ;
	}
	getcwd(buffer, 1024);
	tmp = ft_strjoin("PWD=", buffer);
	export(exec->data->env, var);
	export(exec->data->env, tmp);
	free (tmp);
	free (var);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:05:31 by pdolinar          #+#    #+#             */
/*   Updated: 2022/10/27 10:33:42 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_var_val(char *str)
{
	int		i;
	char	**list;

	list = malloc(sizeof(char *) * 3);
	if (!list)
		return (NULL);
	list[2] = NULL;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	list[0] = ft_substr(str, 0, i);
	list[1] = ft_substr(str, i + 1, (ft_strlen(str) - i));
	return (list);
}

int	return_builtin(int type, t_exec *cmd)
{
	if (type == PWD)
		pwd();
	else if (type == CD)
		cd(cmd);
	else if (type == ECHO)
		echo(cmd);
	else if (type == EXP)
	{
		if (cmd->cmd->next && cmd->cmd->next->type == ARG)
			export_recursive(cmd->data->env, cmd->cmd->next);
		else
			export(cmd->data->env, NULL);
	}
	else if (type == UNSET)
		unset(cmd->data->env, cmd);
	else if (type == EXIT)
		return (ft_exit(cmd));
	else if (type == ENV)
		env(cmd->data->env);
	else if (type == HISTORY)
		print_hist_list(cmd->data->history);
	return (-1);
}

char	*str_to_lower(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
	return (str);
}

int	ft_emptyline(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input[i] == '\0')
		return (1);
	return (0);
}

int	count_type(t_token *token, int type)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == type)
			count++;
		token = token->next;
	}
	return (count);
}

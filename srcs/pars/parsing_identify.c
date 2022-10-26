/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:53:44 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/22 16:14:42 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	search_redir(char *str, t_data *data)
{
	if (str[0] == '<')
	{
		data->next_is_file = 1;
		return (INPUT);
	}
	else if (str[0] == '>')
	{
		data->next_is_file = 2;
		return (OUTPUT);
	}
	if (data->next_is_file == 1 && !(ft_strlen(str) == 1
			&& ft_strncmp(str, "|", 1) == 0))
	{
		data->next_is_file = 0;
		return (I_FILE);
	}
	else if (data->next_is_file == 2 && !(ft_strlen(str) == 1
			&& ft_strncmp(str, "|", 1) == 0))
	{
		data->next_is_file = 0;
		return (O_FILE);
	}
	else
		return (0);
}

static
int	checkpipe(char *str, t_data *data)
{
	if (ft_strlen(str) == 1 && str[0] == '|')
	{
		if (data->cmd_found == 0)
		{
			ft_error("Syntax error\n");
			g_exit_code = 1;
		}
		data->cmd_found = 0;
		return (1);
	}
	return (0);
}

/* 	Removes almost every Quotes in the string, 
	("he'll'o" -> he'll'o) 
	free the old one, create a new str */
char	*rem_all_quotes(char *old)
{
	char	*new;
	int		i;
	int		j;
	int		s_quote;
	int		d_quote;

	new = malloc(sizeof(char) * (ft_strlen(old) + 1));
	i = -1;
	j = -1;
	s_quote = 0;
	d_quote = 0;
	while (old[++i])
	{
		if (old[i] == '\'' && (d_quote % 2 == 0))
			s_quote++;
		else if (old[i] == '\"' && (s_quote % 2 == 0))
			d_quote++;
		else
			new[++j] = old[i];
	}
	new[++j] = '\0';
	free (old);
	return (new);
}

/* 	check if the string is a builtin
	Return: BUILTIN or EXEC */
static
int	check_builtin(char *str)
{
	char	*newstr;
	char	*builtins;

	builtins = " echo cd pwd export unset env exit history ";
	newstr = ft_custom_strjoin(" ", str, " ");
	if (ft_strnstr(builtins, newstr, 50) == NULL)
	{
		free (newstr);
		return (EXEC);
	}
	else
	{
		free (newstr);
		return (BUILTIN);
	}
}

/* identify the kind of the string */
char	*identify_token(char *str, t_data *data, int *type)
{
	int	redir_ret;

	redir_ret = search_redir(str, data);
	if (checkpipe(str, data))
		*type = PIPE;
	else if (redir_ret != 0)
		*type = redir_ret;
	else if (data->cmd_found == 0)
	{
		str = rem_all_quotes(str);
		str = str_to_lower(str);
		data->num_cmds++;
		data->cmd_found = 1;
		*type = check_builtin(str);
	}
	else if (str[0] == '-')
		*type = FLAG;
	else
		*type = ARG;
	return (str);
}

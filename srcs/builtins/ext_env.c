/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:38:28 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/26 10:41:50 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
char	*combine_exit(int *j, char **parts)
{
	char	*newstr;
	char	*itoa;

	newstr = NULL;
	itoa = ft_itoa(g_exit_code);
	newstr = ft_custom_strjoin(parts[0], itoa, parts[2]);
	*j = ft_strlen(parts[0]) + ft_strlen(itoa) - 1;
	free(itoa);
	return (newstr);
}

/* search the var and put together the new string */
static
char	*put_str_together(t_data *data, int *j, char **parts)
{
	char	*newstr;
	t_env	*tmp;
	char	*diff;

	newstr = NULL;
	tmp = data->env;
	while (tmp)
	{
		if (strenv_cmp(parts[1], tmp->var) == 0)
		{
			diff = ft_strchr(tmp->var, '=');
			if (diff == NULL)
				break ;
			newstr = ft_custom_strjoin(parts[0], diff + 1, parts[2]);
			*j = ft_strlen(parts[0]) + ft_strlen(diff + 1) - 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!newstr)
	{
		newstr = ft_strjoin(parts[0], parts[2]);
		*j = ft_strlen(parts[0]) - 1;
	}
	return (newstr);
}

/* Replace the given var with the value */
static
char	*replace_var(char *arg, int *j, int *varPlace, t_data *data)
{
	char	*parts[3];
	char	*newstr;

	newstr = NULL;
	parts[0] = ft_substr(arg, 0, varPlace[0]);
	parts[1] = ft_substr(arg, varPlace[0] + 1, varPlace[1] - varPlace[0]);
	parts[2] = ft_substr(arg, varPlace[1] + 1, ft_strlen(arg) - varPlace[1]);
	if (ft_strncmp(parts[1], "?", 1) == 0 && ft_strlen(parts[1]) == 1)
		newstr = combine_exit(j, parts);
	else
		newstr = put_str_together(data, j, parts);
	free (arg);
	free (parts[0]);
	free (parts[1]);
	free (parts[2]);
	return (newstr);
}

/* 	input: arg[j] == '
	jump over single quotes */
static
int	handle_quotes(char *arg, int j, int length, int *in_double_quo)
{
	if (arg[j] == '\0')
		return (j);
	if (arg[j] == '\"')
	{
		if (*in_double_quo == 0)
			*in_double_quo = 1;
		else if (*in_double_quo == 1)
			*in_double_quo = 0;
	}
	if (arg[j] == '\'' && *in_double_quo == 0)
	{
		j++;
		while (j < length && arg[j] != '\'')
			j++;
		if (j == length)
			ft_error("syntex error: quotes\n");
	}
	return (j);
}

/* Expands the environment Variables */
//Allowed: Ab_3fd
char	*ext_env_var(char *arg, t_data *data)
{
	int		length;
	int		j;
	int		var_place[2];
	int		in_double_quo;

	in_double_quo = 0;
	length = ft_strlen(arg);
	j = -1;
	while (++j < length)
	{
		j = handle_quotes(arg, j, length, &in_double_quo);
		if (arg[j] && arg[j] == '$')
		{
			var_place[0] = j;
			j++;
			while (ft_isalnum(arg[j]) || arg[j] == '_')
				j++;
			if (var_place[0] == (j - 1) && arg[j] == '?')
				j++;
			var_place[1] = j - 1;
			arg = replace_var(arg, &j, var_place, data);
			length = ft_strlen(arg);
		}
	}
	return (arg);
}

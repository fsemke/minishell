/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:54:37 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/26 19:02:51 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	check_var_name(char *input)
{
	int	i;

	if (ft_isdigit(input[0]) || input[0] == '=')
	{
		write(2, "bash: export: '", 15);
		write(2, input, ft_strlen(input));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	i = -1;
	while (input[++i] && input[i] != '=')
	{
		if (ft_isalnum(input[i]) == 0 && input[i] != '_')
		{
			write(2, "bash: export: '", 15);
			write(2, input, ft_strlen(input));
			write(2, "': not a valid identifier\n", 26);
			return (1);
		}
	}
	return (0);
}

static
void	export_variables(t_env *ptr, char *input)
{
	t_env	*tmp;

	tmp = ptr;
	while (tmp)
	{
		if (strenv_cmp(input, tmp->var) == 0)
		{
			if (ft_strchr(input, '=') != NULL)
			{
				free(tmp->var);
				tmp->var = ft_strdup(input);
				return ;
			}
			else
				return ;
		}
		tmp = tmp->next;
	}
	add_node(&ptr, init_node(input));
}

void	export(t_env *ptr, char *input)
{
	if (ptr == NULL)
	{
		g_exit_code = -1;
		return ;
	}
	else if (input == NULL || ft_strlen(input) == 0)
	{
		print_export(ptr);
		return ;
	}
	else if (check_var_name(input))
	{
		g_exit_code = 1;
		return ;
	}
	export_variables(ptr, input);
}

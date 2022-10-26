/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:43:49 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/26 19:03:16 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	check_next_smaller(t_env **i, char **tmp_smallest,
	char **last_printed, int *changed)
{
	*changed = 0;
	while (*i)
	{
		if (strenv_cmp(*tmp_smallest, (*i)->var) > 0
			&& (strenv_cmp(*last_printed, (*i)->var) < 0
				|| *last_printed == NULL))
		{
			*tmp_smallest = (*i)->var;
			*changed = 1;
		}
		*i = (*i)->next;
	}
}

static
void	print_smallest(char *tmp_smallest)
{
	char	**list;

	if (tmp_smallest)
	{
		list = split_var_val(tmp_smallest);
		if (ft_memchr(tmp_smallest, '=', ft_strlen(tmp_smallest)) != NULL)
			printf("declare -x %s=\"%s\"\n", list[0], list[1]);
		else
			printf("declare -x %s\n", list[0]);
		free(list[0]);
		free(list[1]);
		free(list);
	}
}

void	print_export(t_env *env)
{
	char	*tmp_smallest;
	char	*last_printed;
	t_env	*i;
	int		changed;

	i = env;
	last_printed = NULL;
	tmp_smallest = NULL;
	changed = 1;
	while (changed)
	{
		check_next_smaller(&i, &tmp_smallest, &last_printed, &changed);
		print_smallest(tmp_smallest);
		last_printed = tmp_smallest;
		tmp_smallest = NULL;
		i = env;
	}
}

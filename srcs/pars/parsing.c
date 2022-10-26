/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:08:39 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/26 12:00:07 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	get_process_token(t_data *data, char **tmp, t_token **token)
{
	int	type;

	*tmp = ft_get_next_word(data->input);
	if (!(*tmp))
		return (1);
	if (!(data->tokens))
	{
		*tmp = identify_token(*tmp, data, &type);
		if (g_exit_code != 0)
			return (2);
		*token = ini_token(*tmp, type);
		data->tokens = *token;
		return (0);
	}
	else
	{
		*tmp = identify_token(*tmp, data, &type);
		(*token)->next = ini_token(*tmp, type);
		(*token)->next->previous = *token;
	}
	*token = (*token)->next;
	return (0);
}

/* parse the input into the list */
void	parsing_input(t_data *data)
{
	t_token	*token;
	char	*tmp;

	ini_data(data);
	if (check_quotes(data->input, ft_strlen(data->input)) == 0)
	{
		g_exit_code = ft_error("Syntax error\n");
		return ;
	}
	token = NULL;
	data->input = ext_env_var(data->input, data);
	g_exit_code = 0;
	tmp = "a";
	while (tmp)
	{
		if (get_process_token(data, &tmp, &token) == 1)
			break ;
		if (g_exit_code != 0)
			return ;
	}
	if (after_processing(data->tokens) != 0)
		g_exit_code = 1;
}

int	after_processing(t_token *t)
{
	int	num_cmds;

	num_cmds = 0;
	while (t)
	{
		if (t->type != BUILTIN || t->type != EXEC || t->type != PIPE)
			t->token = rem_all_quotes(t->token);
		if (t->type == BUILTIN || t->type == EXEC)
			num_cmds++;
		t = t->next;
	}
	if (num_cmds < 1)
	{
		write(2, "Syntax error\n", 13);
		return (1);
	}
	return (0);
}

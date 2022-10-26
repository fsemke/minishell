/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:53:00 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/26 11:37:36 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
t_history	*ini_hist_node(t_data *data)
{
	t_history	*history;

	add_history(data->input);
	history = malloc(sizeof(*history));
	if (history == NULL)
		return (NULL);
	history->value = ft_strdup(data->input);
	history->index = ++(data->hist_count);
	history->next = NULL;
	return (history);
}

void	add_hist_node(t_data *data)
{
	t_history	*last;

	if (data->history == NULL)
		data->hist_count = 0;
	last = data->history;
	data->history = ini_hist_node(data);
	data->history->next = last;
}

void	print_hist_list(t_history *history)
{
	if (history->next)
		print_hist_list(history->next);
	if (history->index < 10)
		printf("  %d  %s\n", history->index, history->value);
	else if (history->index < 100)
		printf(" %d  %s\n", history->index, history->value);
	else
		printf("%d  %s\n", history->index, history->value);
}

void	ft_clear_history(t_history *history, t_data *data)
{
	if (history && history->next)
		ft_clear_history(history->next, data);
	if (history == data->history)
		data->history = NULL;
	if (history)
		free (history->value);
	free (history);
}

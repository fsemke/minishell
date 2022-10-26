/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:05:07 by pdolinar          #+#    #+#             */
/*   Updated: 2022/10/26 12:38:37 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

static
int	parse_execute(t_data *data)
{
	int	status;

	status = 0;
	add_hist_node(data);
	parsing_input(data);
	if (g_exit_code == 0)
		check_redir_char(data->tokens);
	if (g_exit_code == 0)
		check_syntax_error(data->tokens);
	if (g_exit_code == 0)
	{
		init_exec(data);
		run_heredoc(data);
		status = ft_exec(data->cmd);
	}
	ft_get_next_word(NULL);
	cleanup_tokens(data);
	cleanup_exec(data);
	return (status);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		status;

	(void)ac;
	(void)av;
	init_shell_env(envp, &data);
	data.history = NULL;
	g_exit_code = 0;
	data.cmd = NULL;
	handle_signal(0);
	status = 0;
	while (status != EXIT_SHELL)
	{
		data.input = readline("$> ");
		if (data.input == NULL)
			break ;
		if (ft_emptyline(data.input))
			continue ;
		status = parse_execute(&data);
	}
	ft_clear_history(data.history, &data);
	clear_nodes(&data.env);
	free (data.redir);
	return (g_exit_code);
}

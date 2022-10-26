/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errorcheck.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:50:05 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/26 12:35:38 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	check_redir_input(t_token *t)
{
	if (ft_strlen(t->token) == 2 && ft_strncmp(t->token, "<<", 2) == 0)
		t->type = HEREDOC;
	else if (ft_strlen(t->token) == 1
		&& ft_strncmp(t->token, "<", 1) == 0)
		t->type = INPUT;
	else
	{
		write(2, "Syntax error near unexpected token '<'\n", 40);
		return (248);
	}
	return (0);
}

/* 	It checks after the parsing, if the redirection signs are valid
	and change it to Heredoc or Append */
void	check_redir_char(t_token *t)
{
	while (t)
	{
		if (t->type == INPUT)
		{
			if (check_redir_input(t) != 0)
				g_exit_code = check_redir_input(t);
		}
		else if (t->type == OUTPUT)
		{
			if (ft_strlen(t->token) == 2 && ft_strncmp(t->token, ">>", 2) == 0)
				t->type = APPEND;
			else if (ft_strlen(t->token) == 1
				&& ft_strncmp(t->token, ">", 1) == 0)
				t->type = OUTPUT;
			else
			{
				write(2, "Syntax error near unexpected token '>'\n", 40);
				g_exit_code = 248;
			}
		}
		t = t->next;
	}
}

int	ft_error(char *s)
{
	write(2, s, ft_strlen(s));
	return (1);
}

void	check_syntax_error(t_token *t)
{
	while (t)
	{
		if ((t->type == INPUT || t->type == OUTPUT
				|| t->type == APPEND || t->type == HEREDOC)
			&& (t->next == NULL || (t->next->type != I_FILE
					&& t->next->type != O_FILE)))
		{
			g_exit_code = ft_error("Syntax error: No cmd after redirection\n");
			return ;
		}
		if (t->type == PIPE && (t->next == NULL || t->next->type == PIPE))
		{
			g_exit_code = ft_error("Syntax error: No command after pipe\n");
			return ;
		}
		if (t->type == I_FILE && t->previous->type != HEREDOC
			&& access(t->token, F_OK) != 0)
		{
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, "\n", 1);
			g_exit_code = 1;
			return ;
		}
		t = t->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:40:45 by fsemke            #+#    #+#             */
/*   Updated: 2022/10/24 12:20:14 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	search_end(const char *s, int *b, int *e)
{
	while ((s[*e] && s[*e] != ' ' && s[*e] != '\t') || check_quotes(s, *e) == 0)
	{
		if (check_quotes(s, *e) == 1)
		{
			if (s[*b] == '|')
			{
				(*e)++;
				break ;
			}
			if (s[*b] != '<' && s[*b] != '>' && s[*b] != '|'
				&& (s[*e] == '<' || s[*e] == '>' || s[*e] == '|'))
				break ;
			if ((s[*b] == '<' || s[*b] == '>')
				&& s[*e] != '<' && s[*e] != '>' && s[*e] != '|')
				break ;
		}
		(*e)++;
	}
}

/* returns the next word from the string */
char	*ft_get_next_word(const char *s)
{
	static int	b = 0;
	static int	e = 0;
	char		*result;

	if (!s || !s[b])
	{
		b = 0;
		e = 0;
		return (NULL);
	}
	while (s[b] && (s[b] == ' ' || s[b] == '\t'))
		b++;
	e = b;
	search_end(s, &b, &e);
	if (b == e)
	{
		b = 0;
		e = 0;
		return (NULL);
	}
	result = ft_substr(s, b, e - b);
	b = e;
	return (result);
}

/* 	check if the given character are in quotes or not
	return: 0 if there is in quotes, 1 if not */
int	check_quotes(const char *input, int i)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		if (input[j] == '\'')
		{
			j++;
			while (j < i && input[j] != '\'')
				j++;
			if (j == i)
				return (0);
		}
		else if (input[j] == '\"')
		{
			j++;
			while (j < i && input[j] != '\"')
				j++;
			if (j == i)
				return (0);
		}
	}
	return (1);
}

/* Return the right type of the builtin */
int	return_type_builtin(char *str)
{
	if (ft_strlen(str) == 3 && ft_strncmp(str, "pwd", 3) == 0)
		return (PWD);
	else if (ft_strlen(str) == 2 && ft_strncmp(str, "cd", 2) == 0)
		return (CD);
	else if (ft_strlen(str) == 4 && ft_strncmp(str, "echo", 4) == 0)
		return (ECHO);
	else if (ft_strlen(str) == 6 && ft_strncmp(str, "export", 6) == 0)
		return (EXP);
	else if (ft_strlen(str) == 5 && ft_strncmp(str, "unset", 5) == 0)
		return (UNSET);
	else if (ft_strlen(str) == 4 && ft_strncmp(str, "exit", 4) == 0)
		return (EXIT);
	else if (ft_strlen(str) == 3 && ft_strncmp(str, "env", 3) == 0)
		return (ENV);
	else if (ft_strlen(str) == 7 && ft_strncmp(str, "history", 7) == 0)
		return (HISTORY);
	return (0);
}

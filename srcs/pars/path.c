/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:05:28 by pdolinar          #+#    #+#             */
/*   Updated: 2022/10/25 21:02:22 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* find PATH line in evnp variable */
char	*find_path(t_env *env)
{
	while (env)
	{
		if (strenv_cmp(env->var, "PATH") == 0)
			break ;
		env = env->next;
	}
	if (env == NULL)
		return (NULL);
	return (env->var + 5);
}

/*	get the path of bash command and verify it */
char	*parse_path(t_env *env, char *cmd)
{
	char	**local_paths;
	char	*final_path;
	char	*path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = find_path(env);
	if (!path)
		return (NULL);
	local_paths = ft_split(path, ':');
	i = 0;
	while (local_paths[i] != NULL)
	{
		final_path = ft_custom_strjoin(local_paths[i++], "/", cmd);
		if (access(final_path, X_OK) == 0)
			break ;
		free(final_path);
		final_path = NULL;
	}
	free_double_p(local_paths);
	return (final_path);
}

char	*ft_custom_strjoin(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	str = malloc(sizeof(char) * len + 1);
	if (!(str))
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy(str + ft_strlen(s1), s2, ft_strlen(s2));
	ft_memcpy(str + ft_strlen(s1) + ft_strlen(s2), s3, ft_strlen(s3));
	str[len] = '\0';
	return (str);
}

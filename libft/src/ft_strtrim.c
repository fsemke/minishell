/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:19:17 by pdolinar          #+#    #+#             */
/*   Updated: 2022/01/26 21:55:33 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_char(const char *s, int c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*str;

	while (*s1 && check_char(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len && check_char(set, s1[len]))
		len--;
	str = ft_substr(s1, 0, (len + 1));
	if (!(str))
		return (NULL);
	return (str);
}

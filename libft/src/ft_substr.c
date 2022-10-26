/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 09:19:17 by pdolinar          #+#    #+#             */
/*   Updated: 2022/01/22 14:00:27 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*new;

	size = ft_strlen(s);
	if (len > size)
		len = size;
	if (start > size)
		len = (0);
	if (s == 0)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!(new))
		return (NULL);
	new = ft_memset(new, '0', len);
	i = 0;
	s = s + start;
	while (i < len && s[i] != '\0')
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 23:20:23 by lin-d             #+#    #+#             */
/*   Updated: 2022/02/11 16:13:54 by lin-d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s);
	str = malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (NULL);
	ft_memcpy(str, s, len);
	str[len] = ('\0');
	return (str);
}

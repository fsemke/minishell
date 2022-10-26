/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:59:17 by pdolinar          #+#    #+#             */
/*   Updated: 2022/01/22 14:00:29 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;

	len = ft_strlen(str);
	while (len)
	{
		if (str[len] == c)
			return ((char *)(str + len));
		len--;
	}
	if (str[len] == (char)c)
		return ((char *)(str + len));
	return (NULL);
}

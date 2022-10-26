/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:59:17 by pdolinar          #+#    #+#             */
/*   Updated: 2022/01/22 14:00:33 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_d;
	size_t	len_s;

	i = 0;
	len_d = ft_strlen(dest);
	len_s = ft_strlen(src);
	if (size == 0)
		return (len_s);
	while ((len_d + i) < (size - 1) && src[i] != '\0')
	{
		dest[len_d + i] = src[i];
		i++;
	}
	dest[len_d + i] = '\0';
	if (size > len_d)
		return (len_d + len_s);
	return (size + len_s);
}

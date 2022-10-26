/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 23:02:13 by pdolinar          #+#    #+#             */
/*   Updated: 2022/01/22 14:00:41 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*r;
	size_t			i;

	r = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (*(r + i) == (unsigned char)c)
			return ((void *)(r + i));
		i++;
	}
	return (NULL);
}

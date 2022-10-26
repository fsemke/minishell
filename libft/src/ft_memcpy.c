/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:19:17 by pdolinar          #+#    #+#             */
/*   Updated: 2022/01/23 12:53:08 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	char	*dst1;
	char	*src1;
	size_t	i;

	dst1 = (char *)dest;
	src1 = (char *)src;
	if (!src && !dest)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst1);
}

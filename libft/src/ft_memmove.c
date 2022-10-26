/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:19:17 by pdolinar          #+#    #+#             */
/*   Updated: 2022/01/23 15:40:28 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char	*dst1;
	unsigned char	*src1;

	if (!dest && !src)
		return (NULL);
	dst1 = (unsigned char *)dest;
	src1 = (unsigned char *)src;
	if (dest > src)
	{
		while (size > 0)
		{
			dst1[size - 1] = src1[size - 1];
			size--;
		}
	}
	else
	{
		ft_memcpy(dest, src, size);
	}
	return (dst1);
}

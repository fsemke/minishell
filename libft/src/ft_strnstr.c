/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:59:17 by pdolinar          #+#    #+#             */
/*   Updated: 2022/01/22 14:00:30 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && (i != len))
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0' && ((i + j) < len))
				return ((char *)haystack + i);
			else
				j++;
		}
		i++;
	}
	return (NULL);
}

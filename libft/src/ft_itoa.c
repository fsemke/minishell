/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:19:17 by pdolinar          #+#    #+#             */
/*   Updated: 2022/01/22 14:04:37 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static
int	size(long int n)
{
	int	len;
	int	extra_char;
	int	t_len;

	len = 0;
	extra_char = 0;
	if (n <= 0)
		extra_char = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	t_len = len + extra_char;
	return (t_len);
}

char	*aux_itoa(long int n, int t_len, char *str)
{
	int	i;

	i = t_len;
	if (n == 0)
		str[0] = ('0');
	if (n < 0)
	{
		n = -(n);
		str[0] = '-';
	}
	while (n)
	{
		str[--i] = n % 10 + '0';
		n /= 10;
	}
	str[t_len] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;

	n = (long int)n;
	str = (char *)malloc(sizeof(char) * (size(n) + 1));
	if (!(str))
		return (NULL);
	str = aux_itoa(n, size(n), str);
	return (str);
}

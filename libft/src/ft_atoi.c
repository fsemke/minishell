/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:19:17 by pdolinar          #+#    #+#             */
/*   Updated: 2022/01/22 18:28:49 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *string)
{
	int	i;
	int	r;
	int	sign;

	i = 0;
	r = 0;
	sign = 1;
	while ((string[i] == ' ') || (string[i] == '\t') || (string[i] == '\n')
		|| (string[i] == '\v') || (string[i] == '\r' ) || (string[i] == '\f'))
	{
		i++;
	}
	if (string[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (string[i] == '+')
		i++;
	while (string[i] >= '0' && string[i] <= '9')
	{
		r = r * 10 + (string[i] - '0');
		i++;
	}
	return (sign * r);
}

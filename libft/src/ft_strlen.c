/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:19:17 by pdolinar          #+#    #+#             */
/*   Updated: 2022/01/22 14:00:32 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *x)
{
	size_t	counter;

	counter = 0;
	while (*x++ != '\0')
		counter++;
	return (counter);
}

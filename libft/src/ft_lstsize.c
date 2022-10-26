/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:51:10 by pdolinar          #+#    #+#             */
/*   Updated: 2022/01/22 14:00:42 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		size;

	if (lst == NULL)
		return (0);
	temp = lst;
	size = 0;
	while (temp != NULL)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

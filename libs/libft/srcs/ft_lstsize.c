/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:00:58 by malee             #+#    #+#             */
/*   Updated: 2023/09/17 21:15:39 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Counts the number of nodes in a list.
*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	idx;
	t_list	*tmp;

	idx = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		idx++;
	}
	return (idx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_verify_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:54:51 by malee             #+#    #+#             */
/*   Updated: 2025/01/09 14:01:45 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_add_id(t_id_list **id_list, char *str)
{
	t_id_list	*new_node;
	t_id_list	*cur;

	new_node = (t_id_list *)ft_calloc(1, sizeof(t_id_list));
	new_node->id = str;
	new_node->next = NULL;
	if (!*id_list)
		*id_list = new_node;
	else
	{
		cur = *id_list;
		while (cur->next)
			cur = cur->next;
		cur->next = new_node;
	}
}

bool	ft_dup_check(t_id_list *id_list, char *str)
{
	t_id_list	*cur;

	cur = id_list;
	while (cur)
	{
		if (ft_strncmp(cur->id, str, ft_strlen(str)) == 0)
			return (true);
		cur = cur->next;
	}
	return (false);
}

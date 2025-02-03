/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:08:43 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 12:28:33 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_add_line(t_p_node *cur, t_p_node **line_head)
{
	while (cur && ft_isspace(cur->val))
		cur = cur->next;
	while (cur && cur->val != '\n')
	{
		ft_add_p_node(&line_head, ft_create_p_node(cur->line, cur->pos,
				cur->val));
		cur = cur->next;
	}
	if (cur && cur->val == '\n')
		line_head = (*line_head)->down;
}
/*
** @brief Creates a table of ordered lines newlines are rid of at this point
** as well as any leading whitespace
** @param cur pointer to the head of the list
** @return pointer to the head of the table
*/
t_p_node	*ft_create_table(t_p_node *cur)
{
	t_p_node	*table_head;
	t_p_node	*line_head;

	line_head = NULL;
	table_head = line_head;
	while (cur)
	{
		ft_add_line(cur, &line_head);
		if (cur)
			cur = cur->next;
	}
	return (table_head);
}

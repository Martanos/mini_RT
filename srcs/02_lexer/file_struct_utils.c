/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:45:49 by malee             #+#    #+#             */
/*   Updated: 2025/02/04 18:10:32 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_f_node	*ft_create_f_node(char val)
{
	t_f_node	*node;

	node = (t_f_node *)ft_calloc(1, sizeof(t_f_node));
	if (!node)
		ft_fatal("Failed to create file node");
	node->val = val;
	return (node);
}

/*
** @brief Adds a new file node to the end of the list
** @param head pointer to the head of the list
** @param new_node pointer to the new file node
*/
void	ft_add_f_node(t_f_node **head, t_f_node *new_node)
{
	t_f_node	*current;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	ft_free_f_list(t_f_node *head)
{
	t_f_node	*current;

	while (head)
	{
		current = head;
		head = head->next;
		free(current);
	}
}

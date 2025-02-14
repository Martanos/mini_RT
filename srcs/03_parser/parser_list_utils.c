/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:59:27 by malee             #+#    #+#             */
/*   Updated: 2025/02/14 12:00:00 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "parser.h"

/*
** @brief Creates a new parser node
** @param str string to be tokenized
** @param dbl double to be tokenized
** @param rgb_val uint32_t to be tokenized
** @return pointer to the new parser node
*/
t_p_node	*ft_create_p_node(char *str)
{
	t_p_node	*node;

	node = (t_p_node *)ft_calloc(1, sizeof(t_p_node));
	if (!node)
		return (ft_error("Failed to create parser node"), NULL);
	node->str = ft_strdup(str);
	if (!node->str)
		return (ft_error("Failed to duplicate string"), NULL);
	node->len = ft_strlen(str);
	return (node);
}

/*
** @brief Adds a new parser node to the end of the list
** @param head pointer to the head of the list
** @param new_node pointer to the new parser node
*/
bool	ft_add_p_node(t_p_node **head, t_p_node *new_node)
{
	t_p_node	*current;

	if (!new_node)
		return (ft_error("Parser node is NULL"));
	if (!*head)
	{
		*head = new_node;
		return (true);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
	new_node->prev = current;
	return (true);
}

/*
** @brief Frees a parser list
** @param head pointer to the head of the list
*/
void	ft_free_p_list(t_p_node *head)
{
	t_p_node	*current;
	t_p_node	*to_free;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		to_free = current;
		current = current->next;
		free(to_free->str);
		free(to_free);
	}
	head = NULL;
}

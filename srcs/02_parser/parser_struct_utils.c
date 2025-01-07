/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:59:27 by malee             #+#    #+#             */
/*   Updated: 2025/01/07 11:38:27 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
** @brief Creates a new parser node
** @param str string to be tokenized
** @param dbl double to be tokenized
** @param rgb_val uint32_t to be tokenized
** @return pointer to the new parser node
*/
t_parser_node	*ft_create_parser_node(char *str, double *dbl,
		uint32_t *rgb_val)
{
	t_parser_node	*node;

	node = (t_parser_node *)ft_calloc(1, sizeof(t_parser_node));
	if (!node)
		return (NULL);
	node->type = PARSER_TYPE_NONE;
	if (str)
		node->str = ft_strdup(str);
	node->dbl = dbl;
	node->rgb_val = rgb_val;
	node->next = NULL;
	return (node);
}

/*
** @brief Adds a new parser node to the end of the list
** @param head pointer to the head of the list
** @param new_node pointer to the new parser node
*/
void	ft_add_parser_node(t_parser_node **head, t_parser_node *new_node)
{
	t_parser_node	*current;

	if (!head)
		*head = new_node;
	current = *head;
	while (current)
		current = current->next;
	current->next = new_node;
}

/*
** @brief Frees a parser node
** @param node pointer to the parser node
*/
void	ft_free_parser_node(t_parser_node *node)
{
	free(node->str);
	free(node->dbl);
	free(node->rgb_val);
	free(node);
	node = NULL;
}

/*
** @brief Frees a parser list
** @param head pointer to the head of the list
*/
void	ft_free_parser_list(t_parser_node *head)
{
	t_parser_node	*current;

	current = head;
	while (current)
		ft_free_parser_node(current);
	free(head);
	head = NULL;
}

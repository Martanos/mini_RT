/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reconstruct_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:45:14 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 18:36:23 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
** @brief Reconstructs strings from parser node list, returns a table
** @param head pointer to the head of the list
** @return pointer to the head of the new list
*/
void	ft_reconstructor(t_p_node **head)
{
	t_p_node	*new_head;
	t_p_node	*cur;

	cur = *head;
	new_head = NULL;
	while (cur)
	{
		ft_skip_whitespace(&cur, &new_head);
		ft_skip_comment(&cur, &new_head);
		ft_reconstruct_str(&cur, &new_head);
	}
	ft_free_parser_list(*head);
	*head = new_head;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:22:29 by malee             #+#    #+#             */
/*   Updated: 2025/01/11 17:35:53 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_ordered_table(t_p_node **head)
{
}

void	ft_reconstruct_str(t_p_node **head)
{
	t_p_node	*new_head;
	t_p_node	*temp;
	char		*str;

	temp = *head;
	new_head = NULL;
	str = NULL;
	while (*head && !ft_isspace((*head)->val))
	{
		if (!ft_isspace((*head)->val))
			str = ft_strjoin(str, (*head)->val);
		(*head) = (*head)->next;
	}
	ft_free_p_list(temp);
}

void	ft_reconstruct_p_node(t_p_node **head)
{
}

/*
** @brief Facilitates the parsing of the file and populating instruction set
** @param master pointer to the master structure
** @return true if successful, false otherwise
*/
bool	ft_parser(t_master **master, char *file_path)
{
	t_p_node	*head;

	head = ft_read_file(file_path);
	ft_reconstruct_p_node(&head);
	ft_populate(master);
	// VERIFY SYNTAX
	// POPULATE INSTRUCTION SET
	return (true);
}

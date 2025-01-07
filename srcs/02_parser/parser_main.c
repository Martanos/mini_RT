/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:22:29 by malee             #+#    #+#             */
/*   Updated: 2025/01/07 19:45:40 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
** @brief Facilitates the parsing of the file and populating instruction set
** @param master pointer to the master structure
** @return true if successful, false otherwise
*/
bool	ft_parser(t_master **master, char *file_path)
{
	t_parser_node	*head;

	head = ft_read_file(file_path);
	if (head == NULL)
		return (false);
	ft_reconstructor(&head);
	if (!ft_type_convert(&head))
		return (false);
	// VERIFY SYNTAX
	// POPULATE INSTRUCTION SET
	return (true);
}

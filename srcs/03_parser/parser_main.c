/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:22:29 by malee             #+#    #+#             */
/*   Updated: 2025/02/12 17:21:14 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_print_p_list(t_p_node *head)
{
	printf("-----String List-----\n");
	while (head)
	{
		if (!head)
			printf("head: [NULL]\n");
		else if (!head->str)
			printf("str: [NULL]\n");
		else
			printf("str: [%s]\n", head->str);
		head = head->next;
	}
}

/*
** @brief Facilitates the parsing of the file
** @param file_path path to the file
** @return pointer to the master structure
*/
t_master	*ft_parser(char *file_path)
{
	t_p_node	*head;
	t_master	*master;

	head = ft_read_file(file_path);
	if (!head)
		return (NULL);
	ft_print_p_list(head);
	master = ft_populate(head);
	ft_free_p_list(head);
	if (!master)
		return (NULL);
	return (master);
}

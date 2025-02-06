/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:24:24 by malee             #+#    #+#             */
/*   Updated: 2025/02/06 14:44:03 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	ft_print_f_list_raw(t_f_node *head)
{
	printf("-----raw-----\n");
	while (head)
	{
		printf("raw: [%c]\n", head->val);
		head = head->next;
	}
}

static void	ft_print_f_list_clean(t_f_node *head)
{
	printf("-----clean-----\n");
	while (head)
	{
		printf("clean: [%c]\n", head->val);
		head = head->next;
	}
}

/*
** @brief Facilitates the reading of the file
** @param file_path path to the file
** @return pointer to the head of a table representation of the file
*/
t_p_node	*ft_read_file(char *file_path)
{
	t_f_node	*raw_data;
	t_f_node	*clean_data;
	t_p_node	*str;

	raw_data = ft_gnl(ft_verify_file_path(file_path));
	if (!raw_data)
		ft_fatal("Empty file");
	ft_print_f_list_raw(raw_data);
	clean_data = ft_clean_data(raw_data);
	ft_print_f_list_clean(clean_data);
	ft_free_f_list(raw_data);
	str = ft_reconstruct_strings(clean_data);
	ft_free_f_list(clean_data);
	return (str);
}

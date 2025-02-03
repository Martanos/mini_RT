/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:24:24 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 16:49:59 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** @brief Facilitates the reading of the file
** @param file_path path to the file
** @return pointer to the head of a table representation of the file
*/
t_p_node	*ft_read_file(char *file_path)
{
	t_f_node	*raw_data;
	t_f_node	*clean_data;
	t_p_node	*table;

	raw_data = ft_gnl(ft_verify_file_path(file_path));
	if (!raw_data)
		ft_fatal("Empty file");
	clean_data = ft_clean_data(raw_data);
	table = ft_create_table(clean_data);
	ft_free_f_list(raw_data);
	ft_free_f_list(clean_data);
	return (table);
}

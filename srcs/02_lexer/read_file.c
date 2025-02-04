/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:24:24 by malee             #+#    #+#             */
/*   Updated: 2025/02/04 18:21:44 by malee            ###   ########.fr       */
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
	t_p_node	*str;

	raw_data = ft_gnl(ft_verify_file_path(file_path));
	if (!raw_data)
		ft_fatal("Empty file");
	clean_data = ft_clean_data(raw_data);
	ft_free_f_list(raw_data);
	str = ft_reconstruct_strings(clean_data);
	ft_print_p_list(str);
	ft_free_f_list(clean_data);
	return (str);
}

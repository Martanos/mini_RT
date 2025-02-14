/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:24:24 by malee             #+#    #+#             */
/*   Updated: 2025/02/14 12:20:37 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** @brief Facilitates the reading of the file
** @param file_path path to the file
** @return pointer to the head of a table representation of the file
*/
t_p_node	*ft_read_file_main(char *file_path)
{
	t_p_node	*str;
	int			fd;

	fd = ft_verify_file_path(file_path);
	if (fd == -1)
		return (NULL);
	str = ft_read_file(fd);
	if (!str)
		return (NULL);
	close(fd);
	return (str);
}

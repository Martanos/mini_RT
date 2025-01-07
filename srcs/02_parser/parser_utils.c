/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:33:45 by malee             #+#    #+#             */
/*   Updated: 2025/01/06 19:34:05 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_list	*ft_read_file(int fd)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;
	t_list *line_list;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
}

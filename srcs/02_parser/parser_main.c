/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:22:29 by malee             #+#    #+#             */
/*   Updated: 2025/01/05 18:01:40 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_parse_file(t_instruction_set **instruction_set, char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		ft_exit(instruction_set, file_path);
}

t_list	*ft_read_file(int fd)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	t_list	*line_list;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
}

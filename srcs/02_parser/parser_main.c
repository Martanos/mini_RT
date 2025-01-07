/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:22:29 by malee             #+#    #+#             */
/*   Updated: 2025/01/07 11:53:45 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_parser(t_instruction_set **instruction_set, char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		ft_exit(instruction_set, file_path);
}

/*
** @brief Reads the file in its entirety and returns a parser node list
** @param fd file descriptor
*/
void	ft_read_file(int fd)
{
	char			buffer[BUFFER_SIZE];
	ssize_t			bytes_read;
	ssize_t			i;
	t_parser_node	*head;

	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			ft_parser_exit();
		i = 0;
		while (buffer[i++])
			ft_add_parser_node(&head, ft_create_parser_node(buffer[i], NULL,
					NULL));
	}
	return (head);
}

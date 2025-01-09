/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_read_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:33:45 by malee             #+#    #+#             */
/*   Updated: 2025/01/09 17:47:09 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
** @brief Creates a parser node list from a file descriptor
** @param fd file descriptor
** @return pointer to the head of the list
*/
t_parser_node	*ft_create_list(int fd)
{
	ssize_t			bytes_read;
	ssize_t			i;
	t_parser_node	*head;
	char			buffer[BUFFER_SIZE];

	head = NULL;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		i = 0;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		while (bytes_read > 0 && i < bytes_read)
			ft_add_parser_node(&head, ft_create_parser_node(PARSER_TYPE_NONE,
					buffer[i++], 0, NULL));
		if (bytes_read > 0)
			ft_bzero(buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		ft_free_parser_list(head);
		perror("Error\nFailed to read file:");
		return (NULL);
	}
	return (head);
}

/*
** @brief Verifies the file path
** @param file_path path to the file
** @return fd if successful, -1 otherwise
*/
static int	ft_verify_file_path(char *file_path)
{
	ssize_t	len;
	int		fd;

	len = ft_strlen(file_path);
	if (len > 255)
	{
		ft_putstr_fd("Error\nFile path too long", 2);
		return (-1);
	}
	if (len < 4 || file_path[len - 1] != 't' || file_path[len - 2] != 'r'
		|| file_path[len - 3] != '.')
	{
		ft_putstr_fd("Error\nInvalid file extension", 2);
		return (-1);
	}
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nFailed to open file:");
		return (-1);
	}
	return (fd);
}

/*
** @brief Facilitates the reading of the file and populating instruction set
** @param file_path path to the file
** @return pointer to the head of the list
*/
t_parser_node	*ft_read_file(char *file_path)
{
	char			buffer[BUFFER_SIZE];
	t_parser_node	*head;
	int				fd;

	fd = ft_verify_file_path(file_path);
	if (fd == -1)
		return (NULL);
	head = ft_create_list(fd);
	close(fd);
	return (head);
}

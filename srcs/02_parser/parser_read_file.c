/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_read_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:33:45 by malee             #+#    #+#             */
/*   Updated: 2025/01/24 07:19:20 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
	if (len < 4 || file_path[len - 1] != 't' || file_path[len - 2] != 'r'
		|| file_path[len - 3] != '.')
		ft_fatal("Invalid file extension expected: .rt");
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		ft_fatal("Failed to open file");
	return (fd);
}

/*
** @brief Creates a parser node list from a file descriptor
** @param fd file descriptor
** @return pointer to the head of the list
*/
static t_p_node	*ft_gnl(int fd)
{
	ssize_t		bytes_read;
	ssize_t		pos;
	t_p_node	*head;
	char		buffer[BUFFER_SIZE];

	head = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		pos = 0;
		while (pos < bytes_read)
			ft_add_p_node_next(&head, ft_create_p_node(0, 0, buffer[pos++]));
		ft_bzero(buffer, BUFFER_SIZE);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		close(fd);
		ft_free_p_list(head);
		ft_fatal("Failed to read file");
	}
	close(fd);
	return (head);
}

/*
** @brief Numbers raw data
** @param head pointer to the head of the raw data
*/
static void	ft_number_raw_data(t_p_node *head)
{
	ssize_t	line;
	ssize_t	pos;

	line = 1;
	pos = 0;
	while (head)
	{
		head->line = line;
		head->pos = pos;
		if (head->val == '\n')
		{
			line++;
			pos = 0;
		}
		else
			pos++;
		head = head->next;
	}
}

/*
** @brief Facilitates the reading of the file
** @param file_path path to the file
** @return pointer to the head of the raw data
*/
t_p_node	*ft_read_file(char *file_path)
{
	t_p_node	*raw_data;

	raw_data = ft_gnl(ft_verify_file_path(file_path));
	if (!raw_data)
		ft_fatal("Empty file");
	ft_number_raw_data(raw_data);
	return (raw_data);
}

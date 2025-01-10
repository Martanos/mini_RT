/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_read_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:33:45 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 21:21:10 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_p_node	*ft_ordered_list(t_p_node **head, ssize_t line)
{
	t_p_node	*new_head;
	ssize_t		pos;

	new_head = NULL;
	pos = 0;
	while (*head && (*head)->val != '\n')
	{
		ft_add_p_node_next(&new_head, ft_create_p_node(line, pos,
				(*head)->val));
		(*head) = (*head)->next;
	}
	return (new_head);
}

/*
** @brief Creates a new parser node list with ordered lines and positions
** @param head pointer to the head of the list
** @return pointer to the head of the new list
*/
static t_p_node	*ft_ordered_table(t_p_node *head)
{
	t_p_node	*new_head;
	ssize_t		line;

	line = 1;
	new_head = NULL;
	while (head)
	{
		ft_add_p_node_down(&new_head, ft_ordered_list(&head, line));
		if (head->val == '\n')
		{
			head = head->next;
			line++;
		}
	}
	ft_free_p_list(head);
	return (new_head);
}

/*
** @brief Creates a parser node list from a file descriptor
** @param fd file descriptor
** @return pointer to the head of the list
*/
static t_p_node	*ft_read_file_to_list(int fd)
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
			ft_add_p_node(&head, ft_create_p_node(0, 0, buffer[pos++]));
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
		ft_fatal("File path too long");
	if (len < 4 || file_path[len - 1] != 't' || file_path[len - 2] != 'r'
		|| file_path[len - 3] != '.')
		ft_fatal("Invalid file extension expected: .rt");
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		ft_fatal("Failed to open file");
	return (fd);
}

/*
** @brief Facilitates the reading of the file and populating instruction set
** @param file_path path to the file
** @return pointer to the head of an ordered table
*/
t_p_node	*ft_read_file(char *file_path)
{
	t_p_node	*head;

	head = ft_order_list(ft_read_file_to_list(ft_verify_file_path(file_path)));
	return (head);
}

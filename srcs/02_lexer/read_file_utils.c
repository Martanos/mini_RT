/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:01:00 by malee             #+#    #+#             */
/*   Updated: 2025/02/06 23:48:25 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
** @brief Verifies the file path
** @param file_path path to the file
** @return fd if successful, -1 otherwise
*/
int	ft_verify_file_path(char *file_path)
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
t_f_node	*ft_gnl(int fd)
{
	ssize_t		bytes_read;
	ssize_t		pos;
	t_f_node	*head;
	char		buffer[BUFFER_SIZE];

	head = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		pos = 0;
		while (pos < bytes_read)
			ft_add_f_node(&head, ft_create_f_node(buffer[pos++]));
		ft_bzero(buffer, BUFFER_SIZE);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		close(fd);
		ft_free_f_list(head);
		ft_fatal("Failed to read file");
	}
	close(fd);
	return (head);
}

/*
** @brief Cleans the data of comments and minimises whitespace
** @param head pointer to the head of the list
** @return pointer to the head of the cleaned list
*/
t_f_node	*ft_clean_data(t_f_node *head)
{
	t_f_node	*clean_data;

	clean_data = NULL;
	while (head)
	{
		if (head->val == '#')
		{
			while (head && head->val != '\n')
				head = head->next;
			if (head && head->val == '\n')
				head = head->next;
		}
		if (head && head->val != '\n' && ft_isspace(head->val))
		{
			ft_add_f_node(&clean_data, ft_create_f_node(' '));
			while (head && head->val != '\n' && ft_isspace(head->val))
				head = head->next;
		}
		if (head)
		{
			ft_add_f_node(&clean_data, ft_create_f_node(head->val));
			head = head->next;
		}
	}
	return (clean_data);
}

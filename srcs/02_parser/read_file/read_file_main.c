/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:24:24 by malee             #+#    #+#             */
/*   Updated: 2025/02/19 18:09:15 by malee            ###   ########.fr       */
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
		return (ft_error("Invalid file extension expected: .rt"), -1);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (ft_error("Failed to open file"), -1);
	return (fd);
}

/*
** @brief Reads the file and returns a list of file nodes
** @param fd file descriptor
** @return pointer to the head of the list
*/
static t_p_node	*ft_read_data(int fd)
{
	ssize_t		bytes_read;
	t_p_node	*head;
	char		buffer[BUFFER_SIZE + 1];

	ft_bzero(buffer, BUFFER_SIZE + 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	head = NULL;
	while (bytes_read > 0)
	{
		if (ft_process_buffer(buffer, &head))
			bytes_read = read(fd, buffer, BUFFER_SIZE);
		else
			bytes_read = -1;
		ft_bzero(buffer, BUFFER_SIZE + 1);
	}
	if (bytes_read == -1)
	{
		close(fd);
		ft_free_p_list(head);
		return (ft_error("Failed to read file"), NULL);
	}
	return (head);
}

// Pops out all space nodes except new lines
/*
** @brief Cleans up the data by removing all space nodes except new lines
** @param head pointer to the head of the list
*/
static void	ft_clean_data(t_p_node **head)
{
	t_p_node	*current;
	t_p_node	*to_free;

	current = *head;
	while (current)
	{
		if (current->str && ft_isspace(current->str[0])
			&& current->str[0] != '\n')
		{
			to_free = current;
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			current = current->next;
			free(to_free->str);
			free(to_free);
		}
		else
			current = current->next;
	}
}

/*
** @brief Facilitates the reading of the file
** @param file_path path to the file
** @return pointer to the head of a table representation of the file
*/
t_p_node	*ft_read_file(char *file_path)
{
	t_p_node	*str;
	int			fd;

	fd = ft_verify_file_path(file_path);
	if (fd == -1)
		return (NULL);
	str = ft_read_data(fd);
	if (!str)
		return (NULL);
	close(fd);
	ft_clean_data(&str);
	return (str);
}

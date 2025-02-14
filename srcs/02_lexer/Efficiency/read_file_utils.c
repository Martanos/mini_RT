/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 23:47:04 by malee             #+#    #+#             */
/*   Updated: 2025/02/14 12:20:48 by malee            ###   ########.fr       */
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
		return (ft_error("Invalid file extension expected: .rt"), -1);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (ft_error("Failed to open file"), -1);
	return (fd);
}

size_t	ft_custom_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

bool	ft_add_to_existing_node(t_p_node **head, char **buffer)
{
	size_t	new_str_len;
	char	*str_to_add;
	char	*temp;
	size_t	i;

	if (!head || !buffer)
		return (ft_error("Head or buffer is NULL"));
	temp = NULL;
	new_str_len = ft_custom_strlen(*buffer);
	str_to_add = (char *)ft_calloc(sizeof(char), new_str_len);
	if (!str_to_add)
		return (ft_error("Failed to allocate memory"));
	i = 0;
	while (**buffer && !ft_isspace(**buffer))
	{
		str_to_add[i] = **buffer;
		(*buffer)++;
		i++;
	}
	temp = ft_strjoin((*head)->str, str_to_add);
	free((*head)->str);
	free(str_to_add);
	(*head)->str = ft_strdup(temp);
	free(temp);
	return (true);
}

bool	ft_add_new_node(t_p_node **head, char **buffer)
{
	size_t	size_if_new_str;
	char	*new_str;
	size_t	i;

	if (!head || !buffer)
		return (ft_error("Head or buffer is NULL"));
	size_if_new_str = ft_custom_strlen(buffer);
	new_str = (char *)ft_calloc(sizeof(char), size_if_new_str);
	if (!new_str)
		return (ft_error("Failed to allocate memory"));
	i = 0;
	while (**buffer && !ft_isspace(**buffer))
	{
		new_str[i] = **buffer;
		(*buffer)++;
		i++;
	}
	if (!ft_add_p_node(head, ft_create_p_node(new_str)))
		return (false);
	free(new_str);
	return (true);
}

bool	ft_process_buffer(char *buffer, ssize_t bytes_read, t_p_node **head)
{
	while (*buffer)
	{
		if (*head && !ft_isspace((*head)->str) && *buffer && *buffer != '\n')
		{
			if (!ft_add_p_node(head, ft_create_p_node(" ")))
				return (false);
			while (*buffer && ft_isspace(*buffer) && *buffer != '\n')
				buffer++;
		}
		else if (*buffer && *buffer == '\n')
		{
			if (!ft_add_p_node(head, ft_create_p_node("\n")))
				return (false);
			buffer++;
		}
		else if (*buffer && !ft_isspace(*buffer))
		{
			if (!ft_add_to_existing_node(head, &buffer))
				return (false);
		}
		else if (!ft_add_new_node(head, &buffer))
			return (false);
	}
	return (true);
}

/*
** @brief Reads the file and returns a list of file nodes
** @param fd file descriptor
** @return pointer to the head of the list
*/
t_p_node	*ft_read_file(int fd)
{
	ssize_t		bytes_read;
	t_p_node	*head;
	char		buffer[BUFFER_SIZE + 1];

	ft_bzero(buffer, BUFFER_SIZE + 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	head = NULL;
	while (bytes_read > 0)
	{
		if (ft_process_buffer(buffer, bytes_read, &head))
		{
			ft_bzero(buffer, BUFFER_SIZE + 1);
			bytes_read = read(fd, buffer, BUFFER_SIZE);
		}
		else
			bytes_read = -1;
	}
	if (bytes_read == -1)
	{
		close(fd);
		ft_free_p_list(head);
		return (ft_error("Failed to read file"), NULL);
	}
	return (head);
}

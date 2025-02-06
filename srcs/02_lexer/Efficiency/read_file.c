/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 23:47:04 by malee             #+#    #+#             */
/*   Updated: 2025/02/06 23:51:09 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

ssize_t	ft_file_size(char *filepath)
{
	int		fd;
	ssize_t	bytes_read;
	ssize_t	total_bytes;
	char	buffer[BUFFER_SIZE];

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		ft_fatal("Failed to open file");
	total_bytes = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		total_bytes += bytes_read;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		close(fd);
		ft_fatal("Failed to read file");
	}
	close(fd);
	return (total_bytes);
}

char	*ft_get_file_data(char *filepath, int fd)
{
	char	*file_data;
	ssize_t	bytes_read;

	if (!file_data)
		ft_fatal("Memory allocation failed");
	bytes_read = read(fd, file_data, *size);
	if (bytes_read != *size)
	{
		close(fd);
		free(file_data);
		ft_fatal("Incomplete file read");
	}
	close(fd);
	return (file_data);
}

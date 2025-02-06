/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 01:24:03 by malee             #+#    #+#             */
/*   Updated: 2025/02/06 22:29:50 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Outputs the character ’c’ to the given file
	descriptor.
*/

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) != 1)
		exit(1);
}

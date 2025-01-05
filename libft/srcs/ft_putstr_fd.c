/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 01:15:31 by malee             #+#    #+#             */
/*   Updated: 2023/09/16 01:25:38 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Outputs the string ’s’ to the given file
	descriptor.
*/

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	idx;

	if (!s)
		return ;
	idx = 0;
	while (s[idx])
	{
		ft_putchar_fd(s[idx], fd);
		idx++;
	}
}

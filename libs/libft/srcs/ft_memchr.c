/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:53:28 by malee             #+#    #+#             */
/*   Updated: 2023/09/13 21:12:49 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  memchr()  function  scans  the  initial n bytes
	of the memory area pointed to by s for the first
	instance of c.  Both c and the  bytes  of
	the memory area pointed to by s are interpreted as
	unsigned char.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	idx;

	idx = -1;
	while (++idx < n)
		if (((unsigned char *)s)[idx] == (unsigned char)c)
			return ((void *)s + idx);
	return (NULL);
}

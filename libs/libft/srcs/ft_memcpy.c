/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:09:21 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 18:23:08 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  The  memcpy()  function  copies  n bytes from memory
	area src to memory area dest.  The memory areas must
	not overlap. */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	idx;

	idx = -1;
	if (dest != src && n)
	{
		while (++idx < n)
			((unsigned char *)dest)[idx] = ((unsigned char *)src)[idx];
	}
	return (dest);
}

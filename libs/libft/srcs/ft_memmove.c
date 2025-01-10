/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:04:58 by malee             #+#    #+#             */
/*   Updated: 2023/09/17 21:30:56 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  The  memmove()  function  copies n bytes from memory area src to
	memory area dest.  The memory areas may overlap: copying takes
	place as though the  bytes in src are first copied into a
	temporary array that does not overlap src or dest, and the bytes
	are then copied from  the  temporary array to dest. */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	len;

	len = 0;
	if (!dest && !src)
		return (NULL);
	if (src < dest)
	{
		len = n;
		while (len > 0)
		{
			len--;
			((unsigned char *)dest)[len] = ((unsigned char *)src)[len];
		}
	}
	else
	{
		len = 0;
		while (len < n)
		{
			((unsigned char *)dest)[len] = ((unsigned char *)src)[len];
			len++;
		}
	}
	return (dest);
}

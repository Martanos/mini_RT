/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:33:15 by malee             #+#    #+#             */
/*   Updated: 2024/04/08 15:40:58 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strlcat() function appends the NUL-terminated string src to the end
	of dst.  It will append at most size - strlen(dst) - 1 bytes, NUL-termi‐
	nating the result. */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	while (src[j] && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + ft_strlen((char *)src));
}

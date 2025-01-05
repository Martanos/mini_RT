/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:17:49 by malee             #+#    #+#             */
/*   Updated: 2023/09/14 19:32:04 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strlcpy() function copies up to size - 1 characters from the NUL-ter‐
		minated string src to dst, NUL-terminating the result. */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	idx;

	idx = 0;
	if (size == 0)
	{
		while (src[idx])
			idx++;
		return (idx);
	}
	while (idx < size - 1 && src[idx] != '\0')
	{
		dst[idx] = src[idx];
		idx++;
	}
	if (idx < size)
		dst[idx] = '\0';
	while (src[idx] != '\0')
		idx++;
	return (idx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:52:07 by malee             #+#    #+#             */
/*   Updated: 2023/09/14 20:02:08 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  memcmp()  function compares the first n bytes (each interpreted as
	unsigned char) of the memory areas s1 and s2. */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	idx;

	idx = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	while (idx < n)
	{
		if (str1[idx] != str2[idx])
			return ((unsigned char)str1[idx] - (unsigned char)str2[idx]);
		idx++;
	}
	return (0);
}

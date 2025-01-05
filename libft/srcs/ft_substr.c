/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:59:16 by malee             #+#    #+#             */
/*   Updated: 2024/04/08 15:42:35 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  Allocates (with malloc(3)) and returns a substring from the string ’s’.
	The substring begins at index ’start’ and is of
	maximum size ’len’ */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	idx;
	size_t	s_len;

	s_len = ft_strlen((char *)s);
	if (!s || *s == '\0' || start >= s_len)
	{
		sub = malloc(1);
		if (sub)
			sub[0] = '\0';
		return (sub);
	}
	if (len > s_len - start)
		len = s_len - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	idx = -1;
	while (++idx < len)
		sub[idx] = s[start + idx];
	sub[len] = '\0';
	return (sub);
}

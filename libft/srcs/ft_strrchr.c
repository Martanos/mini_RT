/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:37:04 by malee             #+#    #+#             */
/*   Updated: 2024/04/08 15:41:19 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Detects and returns the pointer of
	the last occurance of c in string input
	returns 0 if no match is found
*/

#include "libft.h"

char	*ft_strrchr(const char *input, int c)
{
	long long	idx;

	idx = ft_strlen((char *)input);
	if (c == '\0')
		return ((char *)input + idx);
	while (idx >= 0)
	{
		if (input[idx] == (char)c)
			return ((char *)input + idx);
		idx--;
	}
	return (NULL);
}

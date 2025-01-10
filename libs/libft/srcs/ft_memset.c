/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:38:31 by malee             #+#    #+#             */
/*   Updated: 2023/09/13 20:51:37 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Sets a block of memory to a specific value*/

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	idx;

	idx = -1;
	while (++idx < n)
		((unsigned char *)s)[idx] = (unsigned char)c;
	return (s);
}

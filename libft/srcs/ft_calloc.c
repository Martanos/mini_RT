/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:54:35 by malee             #+#    #+#             */
/*   Updated: 2023/09/16 19:03:53 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The calloc() function allocates memory for an array of n elements */
/* of  size bytes each and returns a pointer to the allocated memory. The*/
/* memory is set to zero.  If nmemb or size is 0,  then  calloc() returns*/
/* either  NULL, or a unique pointer value that can later be successfully*/
/* passed to free(). If the multiplication of nmemb and size would result*/
/* in  integer  overflow,then calloc() returns an error.  By contrast, an*/
/* integer overflow would not be detected in the following call  to  mal‐*/
/* loc(), with the result that an incorrectly sized block of memory would*/
/* be allocated:	*/
/* malloc(nmemb * size); */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	size_t	idx;
	size_t	total;
	char	*mem_alloc;

	total = n * size;
	mem_alloc = malloc(total);
	if (mem_alloc == NULL)
		return (NULL);
	idx = 0;
	while (total > 0)
	{
		mem_alloc[idx] = 0;
		total--;
		idx++;
	}
	return ((void *)mem_alloc);
}

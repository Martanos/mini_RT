/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:30:31 by malee             #+#    #+#             */
/*   Updated: 2024/04/08 15:06:08 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  Allocates (with malloc(3)) and returns a new
	string, which is the result of the concatenation
	of ’s1’ and ’s2’ */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	idx;
	size_t	idx_join;
	size_t	len;

	len = (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	s3 = malloc(sizeof(char) * (len));
	if (!s1 || !s2 || s3 == NULL)
		return (NULL);
	idx = -1;
	idx_join = -1;
	while (s1[++idx])
		s3[++idx_join] = s1[idx];
	idx = -1;
	while (s2[++idx])
		s3[++idx_join] = s2[idx];
	s3[++idx_join] = '\0';
	return (s3);
}

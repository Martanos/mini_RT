/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:09:36 by malee             #+#    #+#             */
/*   Updated: 2024/05/15 23:59:04 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  Detects and returns the pointer of
	the first occurance of c in string input
	returns 0 if no match is found */

#include "libft.h"

char	*ft_strchr(const char *input, int c)
{
	while (*input && *input != (char)c)
		++input;
	if (*input == (char)c)
		return ((char *)input);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:41:20 by malee             #+#    #+#             */
/*   Updated: 2024/04/08 15:43:37 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks amount of char characters in a char array */

#include "libft.h"

ssize_t	ft_strlen(char *str)
{
	char	*ptr;

	if (!str)
		return (-1);
	ptr = str;
	while (*ptr)
		ptr++;
	return (ptr - str);
}

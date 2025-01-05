/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:27:37 by malee             #+#    #+#             */
/*   Updated: 2024/04/18 21:45:52 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  The  atoi() function converts the initial portion of the string pointed
	to by nptr to int.  The behavior is the same as

	strtol(nptr, NULL, 10);

	except that atoi() does not detect errors. */

#include "libft.h"

ssize_t	ft_atoi(const char *str)
{
	int		is_negative;
	ssize_t	result;
	ssize_t	max_value;

	max_value = ((ssize_t)(((size_t)-1) >> 1));
	is_negative = 1;
	result = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			is_negative = -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result > max_value / 10
			|| (result == max_value / 10
				&& *str - '0' > max_value % 10))
			return (max_value * is_negative);
		else
			result = (result * 10) + (*str++ - '0');
	}
	return (result * is_negative);
}

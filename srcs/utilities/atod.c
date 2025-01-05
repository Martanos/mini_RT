/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:12:23 by malee             #+#    #+#             */
/*   Updated: 2025/01/05 18:29:22 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_max_int(char *str)
{
	ssize_t	i;

	i = 1;
	while (!ft_is_digit(*str))
		str++;
	while (*str != '\0' && *str != '.')
	{
		str++;
		i++;
	}
	if (i > 10)
		return (true);
	return (false);
}

bool	ft_max_decimals(char *str)
{
	ssize_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			return (true);
		i++;
	}
	return (false);
}

double	ft_atod(char *str)
{
	double	integer_part;
	double	decimal_part;
	double	sign;
}

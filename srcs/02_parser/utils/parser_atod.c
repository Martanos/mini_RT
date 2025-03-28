/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_atod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 05:30:37 by malee             #+#    #+#             */
/*   Updated: 2025/02/14 14:12:29 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	ft_handle_sign(char **str)
{
	if (*str && **str == '-')
	{
		(*str)++;
		return (-1);
	}
	else if (*str && **str == '+')
		(*str)++;
	return (1);
}

static double	ft_handle_integer(char **str)
{
	double	integer;

	integer = 0;
	while (*str && **str && **str != '.')
	{
		if (!ft_isdigit(**str))
		{
			ft_error("Invalid character in integer part");
			return (NAN);
		}
		integer = integer * 10 + (**str - '0');
		if (integer > DOUBLE_MAX)
			ft_warning("Integer part exceeds maximum precise value");
		(*str)++;
	}
	if (*str && **str == '.')
		(*str)++;
	return (integer);
}

static double	ft_handle_decimal(char **str)
{
	double	decimal;
	int		count;

	decimal = 0;
	count = 0;
	while (*str && **str && !ft_isspace(**str))
	{
		if (!ft_isdigit(**str))
		{
			ft_error("Invalid character in decimal part");
			return (NAN);
		}
		decimal = decimal * 10 + (**str - '0');
		count++;
		if (decimal > DOUBLE_MAX)
			ft_warning("Decimal part exceeds maximum precise value");
		(*str)++;
	}
	return (decimal / pow(10, count));
}

double	ft_atod(char *str)
{
	double	integer;
	double	decimal;
	int		sign;

	if (str == NULL)
		return (NAN);
	sign = ft_handle_sign(&str);
	integer = ft_handle_integer(&str);
	decimal = ft_handle_decimal(&str);
	if (isnan(integer) || isnan(decimal))
		return (NAN);
	return (sign * (integer + decimal));
}

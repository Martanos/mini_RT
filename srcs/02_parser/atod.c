/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 05:30:37 by malee             #+#    #+#             */
/*   Updated: 2025/01/27 11:07:05 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	ft_handle_sign(t_p_node **cur)
{
	while (*cur && ((*cur)->val == '-' || (*cur)->val == '+'))
	{
		if ((*cur)->val == '-')
		{
			(*cur) = (*cur)->next;
			return (-1);
		}
		else if ((*cur)->val == '+')
		{
			(*cur) = (*cur)->next;
			return (1);
		}
		(*cur) = (*cur)->next;
	}
	return (1);
}

static double	ft_handle_integer(t_p_node **cur)
{
	double	integer;

	integer = 0;
	while (*cur && (*cur)->val != '.')
	{
		if (!ft_isdigit((*cur)->val))
		{
			ft_format_error(*cur, "Invalid character in integer part");
			integer = NAN;
			break ;
		}
		integer = integer * 10 + ((*cur)->val - '0');
		if (integer > DOUBLE_MAX)
			ft_warning(*cur, "Integer part exceeds maximum precise value");
		(*cur) = (*cur)->next;
	}
	while (*cur && (*cur)->val != '.')
		(*cur) = (*cur)->next;
	if (*cur && (*cur)->val == '.')
		(*cur) = (*cur)->next;
	return (integer);
}

static double	ft_handle_decimal(t_p_node **cur)
{
	double	decimal;
	int		count;

	decimal = 0;
	count = 0;
	while (*cur && !ft_isspace((*cur)->val))
	{
		if (!ft_isdigit((*cur)->val))
		{
			ft_format_error(*cur, "Invalid character in decimal part");
			decimal = NAN;
			break ;
		}
		decimal = decimal * 10 + ((*cur)->val - '0');
		count++;
		if (decimal > DOUBLE_MAX)
			ft_warning(*cur, "Decimal part exceeds maximum precise value");
		(*cur) = (*cur)->next;
	}
	while (*cur && !ft_isspace((*cur)->val))
		(*cur) = (*cur)->next;
	if (isnan(decimal))
		return (NAN);
	return (decimal / pow(10, count));
}

double	ft_atod(t_p_node **cur)
{
	double	integer;
	double	decimal;
	int		sign;

	sign = ft_handle_sign(cur);
	integer = ft_handle_integer(cur);
	decimal = ft_handle_decimal(cur);
	if (isnan(integer) || isnan(decimal))
		return (NAN);
	return (sign * (integer + decimal));
}

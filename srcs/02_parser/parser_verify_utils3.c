/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_verify_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:52:24 by malee             #+#    #+#             */
/*   Updated: 2025/01/09 17:24:22 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_is_double(char **str)
{
	int		dot_count;
	ssize_t	precision;

	dot_count = 0;
	precision = 1;
	if (**str == '.')
		return (false);
	if (**str == '-' || **str == '+')
		(*str)++;
	while (**str && **str != ',')
	{
		if (!ft_isdigit(**str) && **str != '.')
			return (false);
		if (**str == '.')
			dot_count++;
		if (dot_count > 1)
			return (false);
		if (dot_count == 1)
			precision++;
		(*str)++;
	}
	if (precision > 15)
		printf(ORANGE "WARNING: more than 15 significant digits" RESET);
	return (true);
}

bool	ft_check_rgb(char *str)
{
	int	digit_count;
	int	comma_count;

	digit_count = 0;
	comma_count = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
			digit_count++;
		else if (*str == ',')
		{
			digit_count = 0;
			comma_count++;
		}
		else if (!ft_isdigit(*str) && *str != ',')
			return (false);
		if (comma_count > 2 || digit_count > 3)
			return (false);
		str++;
	}
	return (true);
}

bool	ft_check_xyz(char *str)
{
	int	three_count;

	three_count = 0;
	while (*str)
	{
		if (!ft_is_double(&str))
			return (false);
		if (*str == ',')
			str++;
		three_count++;
		if (three_count > 3)
			return (false);
	}
	return (true);
}

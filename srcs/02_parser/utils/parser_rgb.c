/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:43:27 by malee             #+#    #+#             */
/*   Updated: 2025/02/17 19:45:34 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_atorgb(char *str, uint32_t *struct_rgb, int bits)
{
	int	rgb;

	rgb = 0;
	while (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			return (ft_error("Negative RGB values not allowed"), false);
		str++;
	}
	while (*str && (*str != ',' || !ft_isspace(*str)))
	{
		if (!ft_isdigit(*str))
			return (ft_error("Non numeric RGB value"), false);
		rgb = rgb * 10 + *str - '0';
		str++;
	}
	if (!ft_inrange(rgb, 0, 255))
		return (ft_error("RGB value out of range [0, 255]"), false);
	*struct_rgb = rgb << bits;
	return (true);
}

static bool	ft_verify_rgb(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ',')
			count++;
		else if (*str == '-' || *str == '+')
			str++;
		else if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	if (count != 2)
		return (false);
	return (true);
}

bool	ft_get_rgb(uint32_t *rgb, char *str)
{
	char	**split;
	char	**original;

	split = ft_split(str, ',');
	if (!split || !ft_verify_rgb(str))
		return (ft_error("Empty or invalid RGB value found"), false);
	original = split;
	if (split[0] && split[1] && split[2] && split[3])
	{
		while (*split)
			free(*split++);
		return (free(original), ft_error("Invalid RGB format"), false);
	}
	if (!ft_atorgb(split[0], rgb, 16) || !ft_atorgb(split[1], rgb, 8)
		|| !ft_atorgb(split[2], rgb, 0))
	{
		while (*split)
			free(*split++);
		return (free(original), false);
	}
	while (*split)
		free(*split++);
	return (free(original), true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:43:27 by malee             #+#    #+#             */
/*   Updated: 2025/03/08 19:41:09 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	ft_atorgb(char *str)
{
	int	rgb;

	rgb = 0;
	while (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			return (ft_error("Negative RGB values not allowed"), -1);
		str++;
	}
	while (*str && (*str != ',' || !ft_isspace(*str)))
	{
		if (!ft_isdigit(*str))
			return (ft_error("Non numeric RGB value"), -1);
		rgb = rgb * 10 + *str - '0';
		str++;
	}
	if (!ft_inrange(rgb, 0, 255))
		return (ft_error("RGB value out of range [0, 255]"), -1);
	return (rgb);
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
	original = split;
	if (!split || !ft_verify_rgb(str))
	{
		while (*split)
			free(*split++);
		return (free(original), ft_error("Empty or invalid RGB value found"),
			false);
	}
	if (split[0] && split[1] && split[2] && ft_atorgb(split[0]) != -1
		&& ft_atorgb(split[1]) != -1 && ft_atorgb(split[2]) != -1)
	{
		*rgb = (ft_atorgb(split[0]) << 16) | (ft_atorgb(split[1]) << 8);
		*rgb = *rgb | ft_atorgb(split[2]);
		while (*split)
			free(*split++);
		return (free(original), true);
	}
	while (*split)
		free(*split++);
	return (free(original), false);
}

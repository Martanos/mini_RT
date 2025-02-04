/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:43:27 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 18:06:05 by malee            ###   ########.fr       */
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
			return (ft_format_error("Negative RGB values not allowed"), -1);
		str++;
	}
	while (*str && (*str != ',' || !ft_isspace(*str)))
	{
		if (!ft_isdigit(*str))
			return (ft_format_error("Non numeric RGB value"), -1);
		rgb = rgb * 10 + *str - '0';
		str++;
	}
	if (!ft_inrange(rgb, 0, 255))
		return (ft_format_error("RGB value out of range [0, 255]"), -1);
	return (rgb);
}

uint32_t	ft_get_rgb(char *str)
{
	char	**split;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	if (!str)
		return (-1);
	split = ft_split(str, ',');
	if (!split)
		return (ft_format_error("Empty RGB value found"), -1);
	if (split && split[0] && split[1] && split[2])
	{
		r = ft_atorgb(split);
		g = ft_atorgb(split);
		b = ft_atorgb(split);
	}
	if (r == -1 || g == -1 || b == -1)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

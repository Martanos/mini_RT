/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:43:27 by malee             #+#    #+#             */
/*   Updated: 2025/02/06 20:06:48 by malee            ###   ########.fr       */
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
			return (ft_format_error("Negative RGB values not allowed"), 512);
		str++;
	}
	while (*str && (*str != ',' || !ft_isspace(*str)))
	{
		if (!ft_isdigit(*str))
			return (ft_format_error("Non numeric RGB value"), 512);
		rgb = rgb * 10 + *str - '0';
		str++;
	}
	if (!ft_inrange(rgb, 0, 255))
		return (ft_format_error("RGB value out of range [0, 255]"), 512);
	return (rgb);
}

bool	ft_get_rgb(uint32_t *rgb, char *str)
{
	char	**split;
	int		r;
	int		g;
	int		b;
	char	**original;

	split = ft_split(str, ',');
	if (!split)
		return (ft_format_error("Empty RGB value found"), false);
	original = split;
	if (!split[0] || !split[1] || !split[2] || split[3])
	{
		while (*split)
			free(*split++);
		return (free(original), ft_format_error("Invalid RGB format"), false);
	}
	r = ft_atorgb(split[0]);
	g = ft_atorgb(split[1]);
	b = ft_atorgb(split[2]);
	while (*split)
		free(*split++);
	free(original);
	if (r > 255 || g > 255 || b > 255)
		return (false);
	return (*rgb = (r << 16) | (g << 8) | b, true);
}

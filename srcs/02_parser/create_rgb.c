/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:43:27 by malee             #+#    #+#             */
/*   Updated: 2025/01/27 15:13:44 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	ft_atorgb(t_p_node **cur)
{
	int	rgb;

	rgb = 0;
	while (*cur && ((*cur)->val == '+' || (*cur)->val == '-'))
	{
		if ((*cur)->val == '-')
			return (ft_format_error(cur,
					"Invalid RGB value negative value not allowed"), -1);
		(*cur) = (*cur)->next;
	}
	while (*cur && ((*cur)->val != ',' || !ft_isspace((*cur)->val)))
	{
		if (!ft_isdigit((*cur)->val))
			return (ft_format_error(cur,
					"Invalid RGB value non numeric value detected"), -1);
		rgb = rgb * 10 + (*cur)->val - '0';
		(*cur) = (*cur)->next;
	}
	if (!ft_inrange(rgb, 0, 255))
		return (ft_format_error(cur, "Invalid RGB value out of range"), -1);
	return (rgb);
}

uint32_t	ft_get_rgb(t_p_node **cur)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	while (*cur && (*cur)->val == ' ')
		(*cur) = (*cur)->next;
	r = ft_atorgb(cur);
	g = ft_atorgb(cur);
	b = ft_atorgb(cur);
	if (r == -1 || g == -1 || b == -1)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:03:43 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 17:07:38 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librgb.h"

/*
** @brief Converts a uint32_t color to a t_rgb struct
** @param color The color to convert
** @return The converted color
*/
t_rgb	ft_int_to_rgb(uint32_t color)
{
	t_rgb	temp_color;

	temp_color.r = (color >> 16) & 0xFF;
	temp_color.g = (color >> 8) & 0xFF;
	temp_color.b = color & 0xFF;
	return (temp_color);
}

/*
** @brief Converts a t_rgb struct to a uint32_t color
** @param rgb The color to convert
** @return The converted color
*/
uint32_t	ft_rgb_to_color(t_rgb rgb)
{
	int	ir;
	int	ig;
	int	ib;

	ir = fmin(fmax(rgb.r * 255, 0), 255);
	ig = fmin(fmax(rgb.g * 255, 0), 255);
	ib = fmin(fmax(rgb.b * 255, 0), 255);
	return ((ir << 16) | (ig << 8) | ib);
}

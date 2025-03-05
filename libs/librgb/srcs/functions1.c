/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:17:40 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 10:16:34 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/librgb.h"

/*
** @brief Gets the red value (1st 8 bits) from an rgb value
** @param rgb rgb value
** @return red value
*/
uint32_t	ft_get_r(uint32_t rgb)
{
	return ((rgb >> 16) & 0xFF);
}

/*
** @brief Gets the green value (2nd 8 bits) from an rgb value
** @param rgb rgb value
** @return green value
*/
uint32_t	ft_get_g(uint32_t rgb)
{
	return ((rgb >> 8) & 0xFF);
}

/*
** @brief Gets the blue value (3rd 8 bits) from an rgb value
** @param rgb rgb value
** @return blue value
*/
uint32_t	ft_get_b(uint32_t rgb)
{
	return (rgb & 0xFF);
}

/*
** @brief Color multiplication (for light calculations)
** @param c1 first color
** @param c2 second color
** @return new color
*/
uint32_t	ft_color_multiply(uint32_t c1, uint32_t c2)
{
	double	r1;
	double	g1;
	double	b1;
	double	r2;
	double	g2;
	double	b2;

	ft_color_to_rgb(c1, &r1, &g1, &b1);
	ft_color_to_rgb(c2, &r2, &g2, &b2);
	return (ft_rgb_to_color(r1 * r2, g1 * g2, b1 * b2));
}

/*
** @brief Color scaling
** @param color color to scale
** @param t scaling factor
** @return scaled color
*/
uint32_t	ft_color_scale(uint32_t color, double t)
{
	double	r;
	double	g;
	double	b;

	ft_color_to_rgb(color, &r, &g, &b);
	return (ft_rgb_to_color(r * t, g * t, b * t));
}

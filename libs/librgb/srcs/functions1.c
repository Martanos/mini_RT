/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:17:40 by malee             #+#    #+#             */
/*   Updated: 2025/02/06 22:32:01 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/librgb.h"

/*
** @brief Creates a new rgb value
** @param r red value
** @param g green value
** @param b blue value
** @return new rgb value
*/
uint32_t	ft_create_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return ((r << 16) | (g << 8) | b);
}

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

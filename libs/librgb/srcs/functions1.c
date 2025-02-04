/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:17:40 by malee             #+#    #+#             */
/*   Updated: 2025/02/04 15:36:05 by seayeo           ###   ########.fr       */
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
	return ((r << 16) | (g << 8) | b & 0xFF);
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
** @brief Gets the alpha value (4th 8 bits) from an rgb value
** @param rgb rgb value
** @return alpha value
*/
uint32_t	ft_get_a(uint32_t rgb)
{
	return ((rgb >> 24) & 0xFF);
}

/*
** @brief Gets the red, green, and blue values from an rgb value
** @param rgb rgb value
** @param rgb_arr array to store red, green, and blue values
*/
void	ft_convert_rgb_arr(uint32_t rgb, uint8_t *rgb_arr)
{
	if (!rgb_arr)
		return ;
	rgb_arr[0] = (rgb >> 16) & 0xFF;  // red
	rgb_arr[1] = (rgb >> 8) & 0xFF;   // green
	rgb_arr[2] = rgb & 0xFF;          // blue
}

/*
** @brief Clamps RGB values between 0 and 255
** @param final pointer to array of double values to be clamped
** @param rgb_arr pointer to array to store the clamped uint8_t values
*/
void	ft_clamp_rgb_values(double *final, uint8_t *rgb_arr)
{
	if (!final || !rgb_arr)
		return ;
	rgb_arr[0] = (uint8_t)fmin(fmax(final[0], 0), 255);
	rgb_arr[1] = (uint8_t)fmin(fmax(final[1], 0), 255);
	rgb_arr[2] = (uint8_t)fmin(fmax(final[2], 0), 255);
}

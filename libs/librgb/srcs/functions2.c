/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:31:37 by malee             #+#    #+#             */
/*   Updated: 2025/03/08 09:57:36 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librgb.h"

/*
** @brief Gets the red, green, and blue values from an rgb value
** @param rgb rgb value
** @param rgb_arr array to store red, green, and blue values
*/
void	ft_convert_rgb_arr(uint32_t rgb, uint8_t *rgb_arr)
{
	if (!rgb_arr)
		return ;
	rgb_arr[0] = (rgb >> 16) & 0xFF;
	rgb_arr[1] = (rgb >> 8) & 0xFF;
	rgb_arr[2] = rgb & 0xFF;
}

/*
** @brief Clamps RGB values between 0 and 255
** @param final pointer to array of double values to be clamped
** @param rgb_arr pointer to array to store the clamped uint8_t values
*/
void	ft_clamp_rgb_values(uint8_t *final, uint8_t *rgb_arr)
{
	if (!final || !rgb_arr)
		return ;
	rgb_arr[0] = (uint8_t)fmin(fmax(final[0], 0), 255);
	rgb_arr[1] = (uint8_t)fmin(fmax(final[1], 0), 255);
	rgb_arr[2] = (uint8_t)fmin(fmax(final[2], 0), 255);
}

/*
** @brief Adds the values of the second RGB array to the first RGB array
** @param rgb_arr1 First RGB array (will contain the sum)
** @param rgb_arr2 Second RGB array to add
*/
void	ft_color_add(uint8_t *rgb_arr1, uint8_t *rgb_arr2)
{
	rgb_arr1[0] = (uint8_t)fmin(rgb_arr1[0] + rgb_arr2[0], 255);
	rgb_arr1[1] = (uint8_t)fmin(rgb_arr1[1] + rgb_arr2[1], 255);
	rgb_arr1[2] = (uint8_t)fmin(rgb_arr1[2] + rgb_arr2[2], 255);
}

/*
** @brief Mixes the values of two RGB arrays based on a ratio
** @param rgb_arr1 First RGB array (will contain the result)
** @param rgb_arr2 Second RGB array to mix
** @param ratio Ratio of the first array in the mix (0.0 to 1.0)
*/
void	ft_color_mixer(uint8_t *rgb_arr1, uint8_t *rgb_arr2, double ratio)
{
	double	second_ratio;

	second_ratio = 1 - ratio;
	rgb_arr1[0] = (uint8_t)fmin(rgb_arr1[0] * ratio + rgb_arr2[0]
			* (second_ratio), 255);
	rgb_arr1[1] = (uint8_t)fmin(rgb_arr1[1] * ratio + rgb_arr2[1]
			* (second_ratio), 255);
	rgb_arr1[2] = (uint8_t)fmin(rgb_arr1[2] * ratio + rgb_arr2[2]
			* (second_ratio), 255);
}

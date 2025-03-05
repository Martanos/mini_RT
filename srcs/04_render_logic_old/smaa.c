/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smaa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:38:37 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/16 13:22:20 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

uint32_t	get_pixel(t_master *master, int x, int y)
{
	char	*pixel;

	pixel = master->img.pixels_ptr + (y * master->img.line_len + x
			* (master->img.bpp / 8));
	return (*(uint32_t *)pixel);
}

void	luminance(uint8_t *rgb)
{
	uint8_t	gray;

	gray = (uint8_t)(0.299 * rgb[0] + 0.587 * rgb[1] + 0.114 * rgb[2]);
	rgb[0] = gray;
	rgb[1] = gray;
	rgb[2] = gray;
}

// use greyscale luminance to grade the map into grayscale
// allocate mem for edge map
// use sobel operator to fill edge map
// use sqrt of sobel x^2 + y^2 to get edge strength
// based on edge strength, we can know where the edges are
// for all the edges, call for colour smoothing against the surrounding pixels
void	apply_smaa(t_master *master)
{
	int x;
	int y;
	// double	edge_map[WINDOW_WIDTH][WINDOW_HEIGHT];
	// double	edge_strength[WINDOW_WIDTH][WINDOW_HEIGHT];
	uint8_t temp[3];

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			ft_convert_rgb_arr(get_pixel(master, x, y), temp);
			luminance(temp);
			my_pixel_put(&master->img, x, y, ft_create_rgb(temp[0], temp[1],
					temp[2]));
			x++;
		}
		y++;
	}
}
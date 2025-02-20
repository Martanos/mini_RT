/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:30:45 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/20 12:53:50 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	apply_texture(t_texture texture, double u, double v, uint32_t *color)
{
	int	x;
	int	y;

	x = (int)(u * texture.width) % texture.width;
	y = (int)(v * texture.height) % texture.height;
	if (y * texture.width + x < 0 || y * texture.width + x >= texture.width
		* texture.height)
		*color = texture.pri_color;
	else
		*color = texture.data[y * texture.width + x];
}

static void	apply_bump(t_bump_map bump, double u, double v, uint32_t *color)
{
	int	x;
	int	y;

	x = (int)(u * bump.width) % bump.width;
	y = (int)(v * bump.height) % bump.height;
	if (y * bump.width + x < 0 || y * bump.width + x >= bump.width
		* bump.height)
		*color = bump.data[0];
	else
		*color = bump.data[y * bump.width + x];
}

void	apply_tb(t_obj_pro pro, double u, double v, uint32_t *color)
{
	uint32_t	rgb1;
	uint32_t	rgb2;
	uint8_t		rgbarr1[3];
	uint8_t		rgbarr2[3];
	
	printf("applying tb\n");
	apply_texture(pro.txm, u, v, &rgb1);
	apply_bump(pro.bpm, u, v, &rgb2);
	ft_convert_rgb_arr(rgb1, rgbarr1);
	ft_convert_rgb_arr(rgb2, rgbarr2);
	ft_color_mixer(rgbarr1, rgbarr2, 0.4);
	*color = ft_create_rgb(rgbarr1[0], rgbarr1[1], rgbarr1[2]);	
}
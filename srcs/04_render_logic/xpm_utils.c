/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:30:45 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/18 17:48:57 by seayeo           ###   ########.fr       */
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

// void	apply_bump(t_bump_map bump, double u, double v, uint32_t *color)
// {
// 	int	x;
// 	int	y;

// 	x = (int)(u * bump.width) % bump.width;
// 	y = (int)(v * bump.height) % bump.height;
// 	if (y * bump.width + x < 0 || y * bump.width + x >= bump.width
// 		* bump.height)
// 		*color = bump.pri_color;
// 	else
// 		*color = bump.data[y * bump.width + x];
// }
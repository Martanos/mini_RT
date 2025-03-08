/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:30:45 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/08 05:03:36 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	apply_texture(t_texture texture, double u, double v, uint32_t *color)
{
	int	x;
	int	y;

	v = 1.0 - v;
	x = (int)(u * texture.width) % texture.width;
	y = (int)(v * texture.height) % texture.height;
	if (y * texture.width + x < 0 || y * texture.width + x >= texture.width
		* texture.height)
		*color = texture.pri_color;
	else
		*color = texture.data[y * texture.width + x];
}

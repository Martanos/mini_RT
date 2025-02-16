/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:30:45 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/09 18:25:15 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

static	t_texture	load_xpm_texture(t_texture texture)
{
	int	bpp;
	int	size_line;
	int	endian;

	texture.data = (int *)mlx_get_data_addr(texture.img, &bpp, &size_line,
			&endian);
	return (texture);
}

void	apply_texture(t_texture texture, double u, double v, uint32_t *color)
{
	int	x;
	int	y;

	load_xpm_texture(texture);
	x = (int)(u * texture.width) % texture.width;
	y = (int)(v * texture.height) % texture.height;
	*color = texture.data[y * texture.width + x];
}

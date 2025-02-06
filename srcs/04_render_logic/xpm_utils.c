/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:30:45 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/06 17:52:35 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_texture   load_xpm_texture(t_master *master, t_texture texture)
{
	int	bpp;
	int	size_line;
	int	endian;
	
	texture.img = mlx_xpm_file_to_image(master->mlx_ptr, "textures/wood.xpm",
			texture.width, texture.height);
	texture.data = (int *)mlx_get_data_addr(texture.img, &bpp, &size_line, &endian);
	return (texture);
}

void apply_texture(t_texture texture, double u, double v, uint32_t *color) {
	int x = (int)(u * texture.width) % texture.width;
	int y = (int)(v * texture.height) % texture.height;
	*color = texture.data[y * texture.width + x];
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:30:45 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/16 13:25:05 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

static	void	load_xpm_texture(t_texture *texture)
{
	int	bpp;
	int	size_line;
	int	endian;

	if (!texture->data)
	texture->data = (int *)mlx_get_data_addr(texture->img, &bpp, &size_line,
			&endian);
}
static void	wrap_uv(double *u, double *v)
{
*u = fmod(*u, 1.0);
*v = fmod(*v, 1.0);
if (*u < 0.0)
	*u += 1.0;
if (*v < 0.0)
	*v += 1.0;
}

void	apply_texture(t_texture texture, double u, double v, uint32_t *color)
{
	int	x;
	int	y;

	load_xpm_texture(&texture);
	wrap_uv(&u, &v);
	x = (int)(u * (texture.width - 1));
	y = (int)(v * (texture.height - 1));
	if (x < 0)
		x = 0;
	else if (x >= texture.width)
		x = texture.width - 1;
	if (y < 0)
		y = 0;
	else if (y >= texture.height)
		y = texture.height - 1;
	*color = texture.data[y * texture.width + x];
}

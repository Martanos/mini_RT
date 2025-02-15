/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:30:45 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/15 21:31:16 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

static void	load_xpm_texture(t_texture *texture)
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
	// Ensure coordinates are within bounds
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

// static void	load_bump(t_bump_map *bump)
// {
// 	int	bpp;
// 	int	size_line;
// 	int	endian;

// 	if (!bump->data)
// 		bump->data = (int *)mlx_get_data_addr(bump->map, &bpp, &size_line,
// 				&endian);
// }

// void	apply_bump(t_bump_map bump, double u, double v, uint32_t *color)
// {
// 	int x;
// 	int y;

// 	load_bump(&bump);
// 	wrap_uv(&u, &v);

// 	x = (int)(u * (bump.width - 1));
// 	y = (int)(v * (bump.height - 1));

// 	// Ensure coordinates are within bounds
// 	if (x < 0)
// 		x = 0;
// 	else if (x >= bump.width)
// 		x = bump.width - 1;

// 	if (y < 0)
// 		y = 0;
// 	else if (y >= bump.height)
// 		y = bump.height - 1;

// 	*color = bump.data[y * bump.width + x];
// }


// uint32_t    apply_both(t_texture texture, t_bump_map bump, double u, double v)
// {
//     uint32_t    color;
//     uint32_t    bump_color;
//     uint8_t     rgb[3];
//     uint8_t     bump_rgb[3];

//     apply_texture(texture, u, v, &color);
//     apply_bump(bump, u, v, &bump_color);
//     ft_convert_rgb_arr(color, rgb);
//     ft_convert_rgb_arr(bump_color, bump_rgb);
//     ft_add_rgb_arr(rgb, bump_rgb);
//     return (ft_create_rgb(rgb[0], rgb[1], rgb[2]));
// }
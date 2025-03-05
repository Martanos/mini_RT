/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:07:29 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 12:09:50 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * Computes the pixel color with supersampling anti-aliasing
 * Returns true if any of the samples hit something
 */
bool	ft_compute_pixel(t_scene **scene, int x, int y, uint32_t *pixel_color)
{
	bool	hit_anything;
	int		total_samples;

	hit_anything = false;
	if (AA <= 1)
		hit_anything = ft_single_ray(scene, x, y, pixel_color);
	else
		hit_anything = ft_multi_ray(scene, x, y, pixel_color);
	if (hit_anything)
	{
		total_samples = AA * AA;
		z_buffer.r_final = z_buffer.r_sum / total_samples;
		z_buffer.g_final = z_buffer.g_sum / total_samples;
		z_buffer.b_final = z_buffer.b_sum / total_samples;
		pixel_color = z_buffer.r_final << 16 | z_buffer.g_final << 8 | z_buffer.b_final;
		return (true);
	}
	return (false);
}

static void	ft_render_scene(t_scene **scene)
{
	int			x;
	int			y;
	uint32_t	pixel_color;

	y = -1;
	pixel_color = 0;
	while (++y < (*scene)->cam_data.win_height)
	{
		x = -1;
		while (++x < (*scene)->cam_data.win_width)
			if (ft_compute_pixel(scene, x, y, &pixel_color))
				ft_pixel_put(&(*scene)->img, x, y, pixel_color);
	}
}

// TODO: make this a the mlx loop
void	ft_render_main(t_scene **scene)
{
	ft_obj_prep_main(scene);
	ft_render_scene(scene);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:07:29 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 06:23:29 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_reset_buffer(t_scene **scene)
{
	ft_memset((*scene)->z_buffer, 0, sizeof(t_hit)
		* (*scene)->cam_data.win_width * (*scene)->cam_data.win_height);
	(*scene)->z_buffer[0].t = DOUBLE_MAX;
	ft_memset((*scene)->ray_buffer, 0, sizeof(t_ray)
		* (*scene)->cam_data.win_width * (*scene)->cam_data.win_height);
	(*scene)->ray_buffer[0].t_min = EPSILON;
	(*scene)->ray_buffer[0].t_max = DOUBLE_MAX;
}

/**
 * Computes the pixel color with supersampling anti-aliasing
 * Returns true if any of the samples hit something
 */
bool	ft_compute_pixel(t_scene **scene, int x, int y, uint32_t *pixel_color)
{
	uint32_t	final_color;
	bool		hit_anything;
	int			total_samples;
	t_hit		z_buffer;

	z_buffer = (*scene)->z_buffer[0];
	hit_anything = false;
	if (AA <= 1)
		return (ft_single_ray(scene, x, y, pixel_color));
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

bool	ft_render_main(t_scene **scene)
{
	int			x;
	int			y;
	uint32_t	pixel_color;

	y = 0;
	pixel_color = 0;
	while (y < (*scene)->cam_data.win_height)
	{
		x = 0;
		while (x < (*scene)->cam_data.win_width)
		{
			ft_reset_buffer(scene);
			if (ft_compute_pixel(scene, x, y, &pixel_color))
				ft_pixel_put(&(*scene)->img, x, y, pixel_color);
			x++;
		}
		y++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:07:29 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 21:14:03 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_colour_compute_main(t_scene **scene)
{
	ft_get_base_colour(&(*scene)->z_buffer);
	ft_calculate_surface_normal((*scene)->z_buffer);
}

/**
 * Computes the pixel color with supersampling anti-aliasing
 * Returns true if any of the samples hit something
 */
bool	ft_compute_pixel(t_scene **scene, t_z_buffer **z_buffer)
{
	bool	hit_anything;
	int		total_samples;

	hit_anything = false;
	if (AA <= 1)
		hit_anything = ft_single_ray(scene, z_buffer);
	else
		hit_anything = ft_multi_ray(scene, z_buffer);
	if (hit_anything)
	{
		// TODO: replace with ft_get_final_colour
		total_samples = AA * AA;
		z_buffer.r_final = z_buffer.r_sum / total_samples;
		z_buffer.g_final = z_buffer.g_sum / total_samples;
		z_buffer.b_final = z_buffer.b_sum / total_samples;
		pixel_color = z_buffer.r_final << 16 | z_buffer.g_final << 8 | z_buffer.b_final;
	}
	return (hit_anything);
}

static void	ft_render_scene(t_scene **scene)
{
	int			x;
	int			y;
	t_z_buffer	*z_buffer;

	y = -1;
	z_buffer = (t_z_buffer *)ft_calloc(1, sizeof(t_z_buffer));
	while (++y < (*scene)->cam_data.win_height)
	{
		x = -1;
		while (++x < (*scene)->cam_data.win_width)
		{
			ft_memset(z_buffer, 0, sizeof(t_z_buffer));
			z_buffer->hit.img_x = x;
			z_buffer->hit.img_y = y;
			if (ft_compute_pixel(scene, &z_buffer))
				ft_pixel_put(&(*scene)->img, x, y, z_buffer->hit.final_color);
		}
	}
	free(z_buffer);
}

// TODO: make this a the mlx loop
void	ft_render_main(t_scene **scene)
{
	ft_obj_prep_main(scene);
	ft_render_scene(scene);
}

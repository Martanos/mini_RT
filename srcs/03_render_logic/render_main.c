/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:07:29 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 11:31:58 by malee            ###   ########.fr       */
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
	srand(time(NULL));
	hit_anything = ft_ray(scene, z_buffer);
	if (hit_anything)
	{
		total_samples = AA * AA;
		(*z_buffer)->hit.final_color_vect.r = (*z_buffer)->hit.final_color_vect.r
			/ total_samples;
		(*z_buffer)->hit.final_color_vect.g = (*z_buffer)->hit.final_color_vect.g
			/ total_samples;
		(*z_buffer)->hit.final_color_vect.b = (*z_buffer)->hit.final_color_vect.b
			/ total_samples;
		(*z_buffer)->hit.pixel_color = ft_rgb_to_color((*z_buffer)->hit.final_color_vect.r,
				(*z_buffer)->hit.final_color_vect.g,
				(*z_buffer)->hit.final_color_vect.b);
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
				ft_pixel_put(&(*scene)->img, x, y, z_buffer->hit.pixel_color);
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

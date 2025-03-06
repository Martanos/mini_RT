/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:07:29 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 16:49:17 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
		(*z_buffer)->cam_hit.final_color.r = (*z_buffer)->cam_hit.final_color.r
			/ total_samples;
		(*z_buffer)->cam_hit.final_color.g = (*z_buffer)->cam_hit.final_color.g
			/ total_samples;
		(*z_buffer)->cam_hit.final_color.b = (*z_buffer)->cam_hit.final_color.b
			/ total_samples;
		(*z_buffer)->cam_hit.pixel_color = ft_rgb_to_color((*z_buffer)->cam_hit.final_color.r,
				(*z_buffer)->cam_hit.final_color.g,
				(*z_buffer)->cam_hit.final_color.b);
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
			z_buffer->cam_hit.img_x = x;
			z_buffer->cam_hit.img_y = y;
			if (ft_compute_pixel(scene, &z_buffer))
				ft_pixel_put(&(*scene)->img, x, y,
					z_buffer->cam_hit.pixel_color);
		}
	}
	free(z_buffer);
	mlx_put_image_to_window((*scene)->mlx_ptr, (*scene)->win_ptr,
		(*scene)->img.img_ptr, 0, 0);
}

// TODO: make this a the mlx loop
void	ft_render_main(t_scene **scene)
{
	ft_obj_prep_main(scene);
	keyhook_wrapper(scene);
	mousehook_wrapper(scene);
	ft_render_scene(scene);
	mlx_loop((*scene)->mlx_ptr);
}

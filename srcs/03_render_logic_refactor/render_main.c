/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:07:29 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 00:37:05 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	ft_random_double(void)
{
	return (double)rand() / (RAND_MAX + 1.0);
}

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

void	ft_generate_primary_ray(t_scene **scene, int x, int y)
{
	t_ray	*ray;

	ray = (*scene)->ray_buffer;
	ray->u = (x + ray->u_offset) / ((*scene)->cam_data.win_width - 1);
	ray->v = (((*scene)->cam_data.win_height - 1 - y) + ray->v_offset)
		/ ((*scene)->cam_data.win_height - 1);
	ray->u = (2.0 * ray->u - 1.0) * ((*scene)->cam_data.viewport_width / 2.0);
	ray->v = (2.0 * ray->v - 1.0) * ((*scene)->cam_data.viewport_height / 2.0);
	ray->origin = (*scene)->cam_data.cord;
	ray->direction = ft_vect_add((*scene)->cam_data.dir,
			ft_vect_add(ft_vect_mul_all((*scene)->cam_data.right, ray->u),
				ft_vect_mul_all((*scene)->cam_data.up, ray->v)));
	ray->direction = ft_vect_norm(ray->direction);
}

bool	ft_single_ray(t_scene **scene, int x, int y, uint32_t *pixel_color)
{
	(*scene)->ray_buffer[0].u_offset = 0.5;
	(*scene)->ray_buffer[0].v_offset = 0.5;
	ft_generate_primary_ray(scene, x, y);
	if (ft_find_closest_intersection(scene))
	{
		// Calculate color at intersection
		(*scene)->z_buffer[0].pixel_color = ft_compute_pixel_color(scene,
				&(*scene)->ray_buffer[0], &(*scene)->z_buffer[0]);
		return (true);
	}
	return (false);
}

bool	ft_multi_ray(t_scene **scene, int x, int y)
{
	int		i;
	int		j;
	t_hit	sample_hit;

	i = 0;
	while (i < AA)
	{
		j = 0;
		while (j < AA)
		{
			(*scene)->ray_buffer[0].u_offset = (i + ft_random_double()) / AA;
			(*scene)->ray_buffer[0].v_offset = (j + ft_random_double()) / AA;
			ft_generate_primary_ray(scene, x, y);
		}
	}
	for (int i = 0; i < samples; i++)
	{
		for (int j = 0; j < samples; j++)
		{
			// Generate jittered ray for this sample
			// Find closest intersection for this sample
			if (ft_find_closest_intersection(scene, &sample_ray, &sample_hit))
			{
				hit_anything = true;
				// Calculate color for this sample
				sample_color = ft_compute_pixel_color(scene, &sample_ray,
						&sample_hit);
				// Accumulate color components
				r_sum += get_r(sample_color);
				g_sum += get_g(sample_color);
				b_sum += get_b(sample_color);
			}
		}
	}
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

	hit_anything = false;
	if (AA <= 1)
		return (ft_single_ray(scene, x, y));
	// Anti-aliasing is enabled, cast multiple rays
	// If any sample hit something, average the colors
	if (hit_anything)
	{
		total_samples = samples * samples;
		r_sum = r_sum / total_samples;
		g_sum = g_sum / total_samples;
		b_sum = b_sum / total_samples;
		// Store the final color in the z-buffer
		pixel_color = r_sum << 16 | g_sum << 8 | b_sum;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 06:21:37 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 07:48:18 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	ft_random_double(void)
{
	return (double)rand() / (RAND_MAX + 1.0);
}

static void	ft_generate_primary_ray(t_scene **scene, int x, int y)
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

static bool	ft_single_ray(t_scene **scene, int x, int y, uint32_t *pixel_color)
{
	(*scene)->ray_buffer[0].u_offset = 0.5;
	(*scene)->ray_buffer[0].v_offset = 0.5;
	ft_generate_primary_ray(scene, x, y);
	if (ft_find_closest_intersection(scene))
	{
		(*scene)->z_buffer[0].pixel_color = ft_compute_pixel_color(scene,
				&(*scene)->ray_buffer[0], &(*scene)->z_buffer[0]);
		return (true);
	}
	return (false);
}

static bool	ft_multi_ray(t_scene **scene, int x, int y, uint32_t *pixel_color)
{
	int		i;
	int		j;
	bool	hit_anything;
	t_hit	*z_buffer;

	z_buffer = (*scene)->z_buffer;
	i = -1;
	hit_anything = false;
	while (++i < AA)
	{
		j = -1;
		while (++j < AA)
		{
			(*scene)->ray_buffer->u_offset = (i + ft_random_double()) / AA;
			(*scene)->ray_buffer->v_offset = (j + ft_random_double()) / AA;
			ft_generate_primary_ray(scene, x, y);
			if (ft_find_closest_intersection(scene))
			{
				hit_anything = true;
				ft_compute_pixel_color(scene);
				z_buffer->r_sum += ft_get_r(z_buffer->pixel_color);
				z_buffer->g_sum += ft_get_g(z_buffer->pixel_color);
				z_buffer->b_sum += ft_get_b(z_buffer->pixel_color);
			}
		}
	}
	return (hit_anything);
}

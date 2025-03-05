/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 06:21:37 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 21:19:32 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	ft_random_double(void)
{
	return (double)rand() / (RAND_MAX + 1.0);
}

static void	ft_populate_ray(t_scene **scene, t_z_buffer **z_buffer)
{
	(*z_buffer)->ray.u = ((*z_buffer)->hit.img_x + (*z_buffer)->ray.u_offset)
		/ ((*scene)->cam_data.win_width - 1);
	(*z_buffer)->ray.v = (((*scene)->cam_data.win_height - 1
				- (*z_buffer)->hit.img_y) + (*z_buffer)->ray.v_offset)
		/ ((*scene)->cam_data.win_height - 1);
	(*z_buffer)->ray.u = (2.0 * (*z_buffer)->ray.u - 1.0)
		* ((*scene)->cam_data.viewport_width / 2.0);
	(*z_buffer)->ray.v = (2.0 * (*z_buffer)->ray.v - 1.0)
		* ((*scene)->cam_data.viewport_height / 2.0);
	(*z_buffer)->ray.origin = (*scene)->cam_data.cord;
	(*z_buffer)->ray.direction = ft_vect_add((*scene)->cam_data.dir,
			ft_vect_add(ft_vect_mul_all((*scene)->cam_data.right,
					(*z_buffer)->ray.u), ft_vect_mul_all((*scene)->cam_data.up,
					(*z_buffer)->ray.v)));
	(*z_buffer)->ray.direction = ft_vect_norm((*z_buffer)->ray.direction);
}

bool	ft_single_ray(t_scene **scene, t_z_buffer **z_buffer)
{
	(*z_buffer)->ray.u_offset = 0.5;
	(*z_buffer)->ray.v_offset = 0.5;
	ft_populate_ray(scene, z_buffer);
	if (ft_intersect_main(scene))
	{
		(*z_buffer)->hit.pixel_color = ft_compute_pixel_color(scene,
				&(*z_buffer)->ray, &(*z_buffer)->hit);
		return (true);
	}
	return (false);
}

bool	ft_multi_ray(t_scene **scene, int x, int y, uint32_t *pixel_color)
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
			if (ft_intersect_main(scene))
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

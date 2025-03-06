/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 06:21:37 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 14:57:16 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	ft_random_double(void)
{
	return (double)rand() / (RAND_MAX + 1.0);
}

static bool	ft_populate_ray(t_scene **scene, t_z_buffer **z_buffer)
{
	(*z_buffer)->cam_ray.u = ((*z_buffer)->cam_hit.img_x
			+ (*z_buffer)->cam_ray.u_offset) / ((*scene)->cam_data.win_width
			- 1);
	(*z_buffer)->cam_ray.v = (((*scene)->cam_data.win_height - 1
				- (*z_buffer)->cam_hit.img_y) + (*z_buffer)->cam_ray.v_offset)
		/ ((*scene)->cam_data.win_height - 1);
	(*z_buffer)->cam_ray.u = (2.0 * (*z_buffer)->cam_ray.u - 1.0)
		* ((*scene)->cam_data.viewport_width / 2.0);
	(*z_buffer)->cam_ray.v = (2.0 * (*z_buffer)->cam_ray.v - 1.0)
		* ((*scene)->cam_data.viewport_height / 2.0);
	(*z_buffer)->cam_ray.origin = (*scene)->cam_data.cord;
	(*z_buffer)->cam_ray.direction = ft_vect_add((*scene)->cam_data.dir,
			ft_vect_add(ft_vect_mul_all((*scene)->cam_data.right,
					(*z_buffer)->cam_ray.u),
				ft_vect_mul_all((*scene)->cam_data.up,
					(*z_buffer)->cam_ray.v)));
	(*z_buffer)->cam_ray.direction = ft_vect_norm((*z_buffer)->cam_ray.direction);
	return (true);
}

bool	ft_ray(t_scene **scene, t_z_buffer **z_buffer)
{
	int		i;
	int		j;
	bool	hit_anything;

	i = -1;
	hit_anything = false;
	while (++i < AA)
	{
		j = -1;
		while (++j < AA)
		{
			if (i > 0 || j > 0)
			{
				(*z_buffer)->cam_ray.u_offset = (i + ft_random_double()) / AA;
				(*z_buffer)->cam_ray.v_offset = (j + ft_random_double()) / AA;
			}
			if (ft_populate_ray(scene, z_buffer) && ft_closest_hit(scene,
					&(*z_buffer)->cam_hit, &(*z_buffer)->cam_ray))
			{
				hit_anything = true;
				ft_colour_compute(scene, z_buffer);
			}
		}
	}
	return (hit_anything);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:07:29 by malee             #+#    #+#             */
/*   Updated: 2025/02/23 01:43:14 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_camera_setup(t_scene **scene)
{
	double	fov_rad;

	(*scene)->cam_data.dir = ft_vect_norm((*scene)->cam_data.dir);
	(*scene)->cam_data.up = ft_vect_norm(ft_vect_cross((*scene)->cam_data.dir,
				ft_vect_create(0, 1, 0)));
	(*scene)->cam_data.right = ft_vect_norm(ft_vect_cross((*scene)->cam_data.dir,
				(*scene)->cam_data.up));
	(*scene)->cam_data.aspect_ratio = (double)WINDOW_WIDTH
		/ (double)WINDOW_HEIGHT;
	fov_rad = (*scene)->cam_data.fov * M_PI / 180.0;
	(*scene)->cam_data.viewport_height = 2.0 * tan(fov_rad / 2.0);
	(*scene)->cam_data.viewport_width = (*scene)->cam_data.viewport_height
		* (*scene)->cam_data.aspect_ratio;
}

t_ray	ft_get_cam_ray(t_cam *cam, double u, double v)
{
	t_ray	ray;
	t_vect	horizontal;
	t_vect	vertical;
	t_vect	direction;

	ray.origin = cam->cord;
	horizontal = ft_vect_mul_all(cam->right, cam->viewport_width);
	vertical = ft_vect_mul_all(cam->up, cam->viewport_height);
	direction = ft_vect_norm(ft_vect_sub(ft_vect_add(ft_vect_add(ft_vect_mul_all(horizontal,
							u - 0.5), ft_vect_mul_all(vertical, v - 0.5)),
					cam->dir), ray.origin));
	ray.direction = direction;
	ray.t_min = 0.001;
	ray.t_max = INFINITY;
	ray.depth = 0;
	return (ray);
}

bool	ft_calculate_pixel(t_scene **scene, int x, int y)
{
	t_ray	ray;

	ray = ft_get_cam_ray(&(*scene)->cam_data, x, y);
}

bool	ft_render_main(t_scene **scene)
{
	int	x;
	int	y;

	ft_camera_setup(scene);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (ft_calculate_pixel(scene, x, y))
			{
				my_pixel_put(&(*scene)->img, x, y, 0x000000);
			}
			x++;
		}
		y++;
	}
}

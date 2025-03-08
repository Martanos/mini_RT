/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderplane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:17:32 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/08 09:55:13 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

static t_vect	calculate_viewport_up(t_vect camera_dir)
{
	t_vect	world_up;
	t_vect	right;

	world_up = ft_vect_create(0.0, 1.0, 0.0);
	right = ft_vect_norm(ft_vect_cross(camera_dir, world_up));
	return (ft_vect_norm(ft_vect_cross(right, camera_dir)));
}

static t_vect	calculate_viewport_dimensions(t_master *master, double *width)
{
	double	aspect_ratio;
	double	viewport_height;

	aspect_ratio = (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT;
	viewport_height = 2.0 * tan((master->cam_head.fov * M_PI / 180.0) / 2.0);
	*width = viewport_height * aspect_ratio;
	return (ft_vect_norm(master->cam_head.norm));
}

static t_vect	get_viewport_upper_left(t_vect center, t_vect h, t_vect v)
{
	t_vect	half_h;
	t_vect	half_v;

	half_h = ft_vect_div_all(h, 2.0);
	half_v = ft_vect_div_all(v, 2.0);
	return (ft_vect_sub(center, ft_vect_add(half_h, half_v)));
}

// merge this into calculations after extracting camera initialization
static t_vect	get_pixel_position(t_vect upper_left, t_vect h, t_vect v,
		int *pos)
{
	double	u;
	double	v_coord;

	u = (double)pos[0] / (WINDOW_WIDTH - 1);
	v_coord = (double)pos[1] / (WINDOW_HEIGHT - 1);
	return (ft_vect_add(upper_left, ft_vect_add(ft_vect_mul_all(h, u),
				ft_vect_mul_all(v, v_coord))));
}

uint32_t	calculations(int *pos, t_master *master)
{
	t_vect	camera_dir;
	t_vect	viewport_up;
	t_vect	viewport_right;
	t_vect	viewport_hori;
	t_ray	ray;

	camera_dir = calculate_viewport_dimensions(master, &viewport_hori.x);
	viewport_up = calculate_viewport_up(camera_dir);
	viewport_right = ft_vect_norm(ft_vect_cross(camera_dir, viewport_up));
	viewport_hori = ft_vect_mul_all(viewport_right, -viewport_hori.x);
	viewport_up = ft_vect_mul_all(viewport_up, -viewport_hori.x);
	viewport_right = ft_vect_add(master->cam_head.cord,
			ft_vect_mul_all(camera_dir, 0.5));
	ray.origin = master->cam_head.cord;
	ray.direction = get_pixel_position(get_viewport_upper_left(viewport_right,
				viewport_hori, viewport_up), viewport_hori, viewport_up, pos);
	ray.direction = ft_vect_norm(ft_vect_sub(ray.direction, ray.origin));
	return (ray_color(ray, master, 20));
}

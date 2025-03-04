/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_prep_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:29:52 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 00:13:13 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_camera_setup(t_scene **scene)
{
	double	fov_rad;

	(*scene)->cam_data.dir = ft_vect_norm((*scene)->cam_data.dir);
	(*scene)->cam_data.up = ft_vect_norm(ft_vect_cross((*scene)->cam_data.dir,
				ft_vect_create(0, 1, 0)));
	(*scene)->cam_data.right = ft_vect_norm(ft_vect_cross((*scene)->cam_data.dir,
				(*scene)->cam_data.up));
	mlx_get_screen_size((*scene)->mlx_ptr, &(*scene)->cam_data.win_width,
		&(*scene)->cam_data.win_height);
	(*scene)->cam_data.aspect_ratio = (double)(*scene)->cam_data.win_width
		/ (double)(*scene)->cam_data.win_height;
	fov_rad = (*scene)->cam_data.fov * M_PI / 180.0;
	(*scene)->cam_data.viewport_height = 2.0 * tan(fov_rad / 2.0);
	(*scene)->cam_data.viewport_width = (*scene)->cam_data.viewport_height
		* (*scene)->cam_data.aspect_ratio;
}

static bool	ft_z_buffer_setup(t_scene **scene)
{
	(*scene)->z_buffer = (t_hit *)ft_calloc(1, sizeof(t_hit));
	if (!(*scene)->z_buffer)
		return (false);
	(*scene)->z_buffer[0].t = DOUBLE_MAX;
	return (true);
}

static bool	ft_ray_buffer_setup(t_scene **scene)
{
	(*scene)->ray_buffer = (t_ray *)ft_calloc(1, sizeof(t_ray));
	if (!(*scene)->ray_buffer)
		return (false);
	(*scene)->ray_buffer[0].t_min = EPSILON;
	(*scene)->ray_buffer[0].t_max = DOUBLE_MAX;
	return (true);
}

bool	ft_obj_prep_main(t_scene **scene)
{
	ft_camera_setup(scene);
	if (!ft_z_buffer_setup(scene))
		return (ft_error("Failed to setup z buffer"));
	if (!ft_ray_buffer_setup(scene))
		return (ft_error("Failed to setup ray buffer"));
	return (true);
}
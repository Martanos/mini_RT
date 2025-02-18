/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:48:07 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/16 13:34:22 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	get_sphere_uv(t_vect point, double *u, double *v)
{
	t_vect	normalized_point;
	double	phi;
	double	theta;

	normalized_point = ft_vect_norm(point);
	phi = atan2(normalized_point.z, normalized_point.x);
	theta = acos(normalized_point.y);
	*u = (phi + M_PI) / (2 * M_PI);
	*v = theta / M_PI;
}

void	get_plane_uv(t_vect point, t_plane *plane, double *u, double *v)
{
	t_vect	right;
	t_vect	up;
	t_vect	up_vector;
	t_vect	temp_up;

	up_vector = ft_vect_create(0, 1, 0);
	// Handle case where plane normal is parallel to up_vector
	if (fabs(ft_vect_dot(plane->norm, up_vector)) > 0.99)
		temp_up = ft_vect_create(0, 0, 1); // Use different reference vector
	else
		temp_up = up_vector;
	right = ft_vect_cross(temp_up, plane->norm);
	if (ft_vect_mag(right) < 1e-6)       // Check if cross product is too small
		right = ft_vect_create(1, 0, 0); // Use fallback vector
	right = ft_vect_norm(right);
	up = ft_vect_norm(ft_vect_cross(plane->norm, right));
	// Calculate relative position from plane's center point
	t_vect relative_pos = ft_vect_sub(point, plane->cord);
	
	// Project onto the plane's coordinate system
	*u = ft_vect_dot(relative_pos, right);
	*v = ft_vect_dot(relative_pos, up);
	
	// Fixed scale factor - adjust this to control texture size
	// Smaller value = larger texture, larger value = smaller texture
	const double scale = 0.02;
	
	// Scale coordinates relative to plane's center
	*u = *u * scale;
	*v = *v * scale;
	
	// Center the coordinates in [0,1] range
	*u = 0.5 + *u;
	*v = 0.5 + *v;
	
	// Clamp coordinates to [0,1] range to prevent texture repetition
	*u = fmax(0.0, fmin(1.0, *u));
	*v = fmax(0.0, fmin(1.0, *v));
}

// void	get_cylinder_uv(t_vect point, t_cylinder *cylinder, double *u,
// 		double *v)
// {
// 	t_vect	local_point;
// 	t_vect	up_vector;
// 	t_vect	temp_cross;
// 	t_vect	double_cross;
// 	double	angle;

// 	up_vector = ft_vect_create(0, 1, 0);
// 	local_point = ft_vect_sub(point, cylinder->cord);
// 	*v = ft_vect_dot(local_point, cylinder->norm) / cylinder->height;
// 	*v = fmod(*v, 1.0);
// 	if (*v < 0)
// 		*v += 1.0;
// 	temp_cross = ft_vect_cross(cylinder->norm, up_vector);
// 	double_cross = ft_vect_cross(cylinder->norm, temp_cross);
// 	angle = atan2(ft_vect_dot(local_point, temp_cross),
// 			ft_vect_dot(local_point, double_cross));
// 	*u = 0.5 + (angle / (2 * M_PI));
// }

// void	get_cone_uv(t_vect point, t_cone *cone, double *u, double *v)
// {
// 	t_vect	local_point;
// 	t_vect	up_vector;
// 	t_vect	temp_cross;
// 	t_vect	double_cross;
// 	double	angle;

// 	up_vector = ft_vect_create(0, 1, 0);
// 	local_point = ft_vect_sub(point, cone->cord);
// 	*v = ft_vect_dot(local_point, cone->norm) / cone->height;
// 	*v = fmod(*v, 1.0);
// 	if (*v < 0)
// 		*v += 1.0;
// 	temp_cross = ft_vect_cross(cone->norm, up_vector);
// 	double_cross = ft_vect_cross(cone->norm, temp_cross);
// 	angle = atan2(ft_vect_dot(local_point, temp_cross),
// 			ft_vect_dot(local_point, double_cross));
// 	*u = 0.5 + (angle / (2 * M_PI));
// }

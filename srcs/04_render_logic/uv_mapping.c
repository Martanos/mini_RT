/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:48:07 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/08 04:16:38 by malee            ###   ########.fr       */
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

// Handle case where plane normal is parallel to up_vector
// Check if cross product is too small
// Calculate relative position from plane's center point
// Project onto the plane's coordinate system
// Center the coordinates in [0,1] range
void	get_plane_uv(t_vect point, t_plane *plane, double *u, double *v)
{
	t_vect	right;
	t_vect	up;
	t_vect	up_vector;
	double	scale;
	t_vect	relative_pos;

	scale = 0.04;
	up_vector = ft_vect_create(0, 1, 0);
	if (fabs(ft_vect_dot(plane->norm, up_vector)) > 0.99)
		right = ft_vect_cross(ft_vect_create(0, 0, 1), plane->norm);
	else
		right = ft_vect_cross(up_vector, plane->norm);
	if (ft_vect_mag(right) < 1e-6)
		right = ft_vect_create(1, 0, 0);
	right = ft_vect_norm(right);
	up = ft_vect_norm(ft_vect_cross(plane->norm, right));
	relative_pos = ft_vect_sub(point, plane->cord);
	*u = ft_vect_dot(relative_pos, right);
	*v = ft_vect_dot(relative_pos, up);
	*u = *u * scale;
	*v = *v * scale;
	*u = 0.5 + *u;
	*v = 0.5 + *v;
}

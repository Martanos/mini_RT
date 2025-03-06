/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:17:34 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 12:10:38 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Calculate UV coordinates on the plane for texture mapping
 */
static void	ft_calculate_plane_uv(t_hit **hit)
{
	t_vect	up;
	t_vect	u_axis;
	t_vect	v_axis;

	if (fabs((*hit)->normal.y) > 0.9)
		up = (t_vect){1, 0, 0};
	else
		up = (t_vect){0, 1, 0};
	u_axis = ft_vect_norm(ft_vect_cross(up, (*hit)->normal));
	v_axis = ft_vect_cross((*hit)->normal, u_axis);
	(*hit)->u = ft_vect_dot((*hit)->point, u_axis);
	(*hit)->v = ft_vect_dot((*hit)->point, v_axis);
	(*hit)->u *= 0.1;
	(*hit)->v *= 0.1;
	(*hit)->u = (*hit)->u - floor((*hit)->u);
	(*hit)->v = (*hit)->v - floor((*hit)->v);
}

/*
 * Calculate ray-plane intersection
 * Returns true if a valid intersection is found within the ray's range
 */
bool	ft_intersect_plane(t_scene **scene, t_obj_data *plane, t_hit **hit,
		t_ray **ray)
{
	double	denom;
	t_vect	oc;
	double	t;

	denom = ft_vect_dot(plane->norm_dir, (*ray)->direction);
	if (fabs(denom) < EPSILON)
		return (false);
	oc = ft_vect_sub(plane->cord, (*ray)->origin);
	t = ft_vect_dot(oc, plane->norm_dir) / denom;
	if (t < (*ray)->t_min || t > (*ray)->t_max || t >= (*hit)->t)
		return (false);
	(*hit)->t = t;
	(*hit)->point = ft_vect_add((*ray)->origin,
			ft_vect_mul_all((*ray)->direction, t));
	(*hit)->normal = plane->norm_dir;
	(*hit)->object = plane;
	(*hit)->front_face = ft_vect_dot((*ray)->direction, plane->norm_dir) < 0;
	if (!(*hit)->front_face)
		(*hit)->normal = ft_vect_mul_all(plane->norm_dir, -1);
	ft_calculate_plane_uv(hit);
	return (true);
}

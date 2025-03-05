/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:17:34 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 10:42:47 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Calculate UV coordinates on the plane for texture mapping
 */
static void	ft_calculate_plane_uv(t_hit *hit)
{
	t_vect	up;
	t_vect	u_axis;
	t_vect	v_axis;

	if (fabs(hit->normal.y) > 0.9)
		up = (t_vect){1, 0, 0};
	else
		up = (t_vect){0, 1, 0};
	u_axis = ft_vect_norm(ft_vect_cross(up, hit->normal));
	v_axis = ft_vect_cross(hit->normal, u_axis);
	hit->u = ft_vect_dot(hit->point, u_axis);
	hit->v = ft_vect_dot(hit->point, v_axis);
	hit->u *= 0.1;
	hit->v *= 0.1;
	hit->u = hit->u - floor(hit->u);
	hit->v = hit->v - floor(hit->v);
}

/*
 * Calculate ray-plane intersection
 * Returns true if a valid intersection is found within the ray's range
 */
bool	ft_intersect_plane(t_scene **scene, t_obj_data *plane)
{
	t_vect	normal;
	double	denom;
	t_vect	oc;
	double	t;

	normal = plane->norm_dir;
	denom = ft_vect_dot(normal, (*scene)->ray.direction);
	if (fabs(denom) < EPSILON)
		return (false);
	oc = ft_vect_sub(plane->cord, (*scene)->ray.origin);
	t = ft_vect_dot(oc, normal) / denom;
	if (t < (*scene)->ray.t_min || t > (*scene)->ray.t_max
		|| t >= (*scene)->hit.t)
		return (false);
	(*scene)->hit.t = t;
	(*scene)->hit.point = ft_vect_add((*scene)->ray.origin,
			ft_vect_mul_all((*scene)->ray.direction, t));
	(*scene)->hit.normal = normal;
	(*scene)->hit.object = plane;
	(*scene)->hit.front_face = ft_vect_dot((*scene)->ray.direction, normal) < 0;
	if (!(*scene)->hit.front_face)
		(*scene)->hit.normal = ft_vect_mul_all(normal, -1);
	ft_calculate_plane_uv(&(*scene)->hit);
	return (true);
}

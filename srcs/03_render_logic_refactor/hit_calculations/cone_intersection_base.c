/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection_base.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:47:01 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 08:01:29 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Calculate cone base center and normal vector
 */
static void	ft_cone_base_properties(t_obj_data *cone, t_vect *base_center,
		t_vect *base_normal)
{
	t_vect	axis;
	double	height;

	axis = cone->norm_dir;
	height = cone->props.t_cone.height;
	*base_center = ft_vect_add(cone->props.t_cone.apex, ft_vect_mul_all(axis,
				height));
	*base_normal = ft_vect_mul_all(axis, -1);
}

/*
 * Calculate the intersection distance (t) with the base plane
 * Returns false if no valid intersection
 */
static bool	ft_base_plane_intersection(t_ray *ray, t_vect base_center,
		t_vect base_normal, double *t)
{
	double	denom;
	t_vect	oc;

	denom = ft_vect_dot(base_normal, ray->direction);
	if (fabs(denom) < EPSILON)
		return (false);
	oc = ft_vect_sub(base_center, ray->origin);
	*t = ft_vect_dot(oc, base_normal) / denom;
	if (*t < ray->t_min || *t > ray->t_max || *t >= ray->depth)
		return (false);
	return (true);
}

/*
 * Check if the intersection point is within the base radius
 */
static bool	ft_is_within_base(t_vect intersection, t_vect base_center,
		t_vect base_normal, double radius)
{
	t_vect	vec_to_center;
	double	dist_squared;

	vec_to_center = ft_vect_sub(intersection, base_center);
	dist_squared = ft_vect_dot(vec_to_center, vec_to_center)
		- pow(ft_vect_dot(vec_to_center, base_normal), 2);
	return (dist_squared <= radius * radius);
}

/*
 * Main function for cone base intersection
 */
bool	ft_intersect_cone_base(t_ray *ray, t_obj_data *cone, t_hit *hit)
{
	double	t;
	double	radius;
	t_vect	intersection;
	t_vect	vec_to_center;
	t_vect	base_center;
	t_vect	base_normal;

	radius = cone->props.t_cone.radius;
	ft_cone_base_properties(cone, &base_center, &base_normal);
	if (!ft_base_plane_intersection(ray, base_center, base_normal, &t))
		return (false);
	intersection = ft_vect_add(ray->origin, ft_vect_mul_all(ray->direction, t));
	vec_to_center = ft_vect_sub(intersection, base_center);
	if (!ft_is_within_base(intersection, base_center, base_normal, radius))
		return (false);
	hit->t = t;
	hit->point = intersection;
	hit->normal = base_normal;
	hit->object = cone;
	hit->front_face = ft_vect_dot(ray->direction, base_normal) < 0;
	if (!hit->front_face)
		hit->normal = ft_vect_mul_all(base_normal, -1);
	hit->u = (vec_to_center.x / radius + 1) * 0.5;
	hit->v = (vec_to_center.z / radius + 1) * 0.5;
	return (true);
}

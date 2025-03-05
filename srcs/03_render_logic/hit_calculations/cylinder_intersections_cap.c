/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersections_cap.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:19:28 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 10:42:52 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_cylinder_cap_properties(t_obj_data *cylinder, bool is_top_cap,
		t_vect *cap_center, t_vect *cap_normal)
{
	t_vect	axis;
	double	half_height;

	axis = cylinder->norm_dir;
	half_height = cylinder->props.t_cylinder.half_height;
	if (is_top_cap)
		*cap_center = ft_vect_add(cylinder->cord, ft_vect_mul_all(axis,
					half_height));
	else
		*cap_center = ft_vect_add(cylinder->cord, ft_vect_mul_all(axis,
					-half_height));
	if (is_top_cap)
		*cap_normal = axis;
	else
		*cap_normal = ft_vect_mul_all(axis, -1);
}

/*
 * Calculate the intersection distance (t) with the cap plane
 * Returns false if no valid intersection
 */
static bool	ft_cap_plane_intersection(t_ray *ray, t_vect cap_center,
		t_vect cap_normal, double *t)
{
	double	denom;
	t_vect	oc;

	denom = ft_vect_dot(cap_normal, ray->direction);
	if (fabs(denom) < EPSILON)
		return (false);
	oc = ft_vect_sub(cap_center, ray->origin);
	*t = ft_vect_dot(oc, cap_normal) / denom;
	if (*t < ray->t_min || *t > ray->t_max || *t >= ray->depth)
		return (false);
	return (true);
}

/*
 * Check if the intersection point is within the cap radius
 */
static bool	ft_is_within_cap(t_vect intersection, t_vect cap_center,
		t_vect cap_normal, double radius)
{
	t_vect	vec_to_center;
	double	dist_squared;

	vec_to_center = ft_vect_sub(intersection, cap_center);
	dist_squared = ft_vect_dot(vec_to_center, vec_to_center)
		- pow(ft_vect_dot(vec_to_center, cap_normal), 2);
	return (dist_squared <= radius * radius);
}

/*
 * Main function for cylinder cap intersection
 */
bool	ft_intersect_cylinder_cap(t_ray *ray, t_obj_data *cylinder, t_hit *hit,
		bool is_top_cap)
{
	double	t;
	t_vect	intersection;
	t_vect	vec_to_center;
	t_vect	cap_center;
	t_vect	cap_normal;

	ft_cylinder_cap_properties(cylinder, is_top_cap, &cap_center, &cap_normal);
	if (!ft_cap_plane_intersection(ray, cap_center, cap_normal, &t))
		return (false);
	intersection = ft_vect_add(ray->origin, ft_vect_mul_all(ray->direction, t));
	if (!ft_is_within_cap(intersection, cap_center, cap_normal,
			cylinder->props.t_cylinder.radius))
		return (false);
	hit->t = t;
	hit->point = intersection;
	hit->normal = cap_normal;
	hit->object = cylinder;
	hit->front_face = ft_vect_dot(ray->direction, cap_normal) < 0;
	if (!hit->front_face)
		hit->normal = ft_vect_mul_all(cap_normal, -1);
	vec_to_center = ft_vect_sub(intersection, cap_center);
	hit->u = (vec_to_center.x / cylinder->props.t_cylinder.radius + 1) * 0.5;
	hit->v = (vec_to_center.z / cylinder->props.t_cylinder.radius + 1) * 0.5;
	return (true);
}

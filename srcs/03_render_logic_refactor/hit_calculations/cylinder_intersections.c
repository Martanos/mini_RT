/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:17:30 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 07:09:24 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Calculate ray intersection with the curved surface of a cylinder
 * Returns true if a valid intersection is found
 */
bool	ft_intersect_cylinder_side(t_ray *ray, t_obj_data *cylinder,
		t_quadratic *quad, t_hit *hit)
{
	t_vect	axis;
	double	radius;
	t_vect	oc;
	t_vect	ray_cross_axis;
	t_vect	oc_cross_axis;
	double	t;
	t_vect	intersection;
	t_vect	vec_to_center;
	double	height_proj;
	t_vect	center_to_hit;

	// Get cylinder axis and radius
	axis = cylinder->norm_dir;
	radius = cylinder->props.t_cylinder.radius;
	// Calculate vectors needed for the quadratic equation
	oc = ft_vect_sub(ray->origin, cylinder->cord);
	// Component of ray direction perpendicular to cylinder axis
	ray_cross_axis = ft_vect_cross(ray->direction, axis);
	oc_cross_axis = ft_vect_cross(oc, axis);
	// Set up quadratic equation coefficients
	quad->a = ft_vect_dot(ray_cross_axis, ray_cross_axis);
	// If a is very small,
	ray is parallel to cylinder axis(no side intersection) if (fabs(quad->a) < 1e-6) return (false);
	quad->b = 2 * ft_vect_dot(ray_cross_axis, oc_cross_axis);
	quad->c = ft_vect_dot(oc_cross_axis, oc_cross_axis) - radius * radius;
	quad->discr = quad->b * quad->b - 4 * quad->a * quad->c;
	// No intersection if discriminant is negative
	if (quad->discr < 0)
		return (false);
	// Calculate intersection distances
	quad->t1 = (-quad->b - sqrt(quad->discr)) / (2 * quad->a);
	quad->t2 = (-quad->b + sqrt(quad->discr)) / (2 * quad->a);
	// Find the closest valid intersection
	if (!ft_quadratic_find_closest_t(quad, ray, hit, &t))
		return (false);
	// Check if intersection point is within the height of the cylinder
	intersection = ft_vect_add(ray->origin, ft_vect_mul_all(ray->direction, t));
	vec_to_center = ft_vect_sub(intersection, cylinder->cord);
	height_proj = ft_vect_dot(vec_to_center, axis);
	if (fabs(height_proj) > cylinder->props.t_cylinder.half_height)
		return (false);
	// Valid intersection found, update hit record
	hit->t = t;
	hit->point = intersection;
	// Calculate normal at intersection point (perpendicular to cylinder axis)
	center_to_hit = ft_vect_sub(hit->point, ft_vect_add(cylinder->cord,
				ft_vect_mul_all(axis, height_proj)));
	hit->normal = ft_vect_norm(center_to_hit);
	hit->object = cylinder;
	// Determine if we hit from inside or outside
	hit->front_face = ft_vect_dot(ray->direction, hit->normal) < 0;
	if (!hit->front_face)
		hit->normal = ft_vect_mul_all(hit->normal, -1);
	// Calculate UV coordinates
	ft_calculate_cylinder_uv(hit, cylinder, height_proj);
	return (true);
}

/*
 * Calculate ray intersection with a cap (top or bottom) of a cylinder
 * Returns true if a valid intersection is found
 */
bool	ft_intersect_cylinder_cap(t_ray *ray, t_obj_data *cylinder, t_hit *hit,
		bool is_top_cap)
{
	t_vect	axis;
	double	half_height;
	double	radius;
	t_vect	cap_center;
	t_vect	cap_normal;
	double	denom;
	t_vect	oc;
	double	t;
	t_vect	intersection;
	t_vect	vec_to_center;
	double	dist_squared;
	double	u;
	double	v;

	axis = cylinder->norm_dir;
	half_height = cylinder->props.t_cylinder.half_height;
	radius = cylinder->props.t_cylinder.radius;
	if (is_top_cap)
		cap_center = ft_vect_add(cylinder->cord, ft_vect_mul_all(axis,
					half_height));
	else
		cap_center = ft_vect_add(cylinder->cord, ft_vect_mul_all(axis,
					-half_height));
	if (is_top_cap)
		cap_normal = axis;
	else
		cap_normal = ft_vect_mul_all(axis, -1);
	denom = ft_vect_dot(cap_normal, ray->direction);
	if (fabs(denom) < EPSILON)
		return (false);
	oc = ft_vect_sub(cap_center, ray->origin);
	t = ft_vect_dot(oc, cap_normal) / denom;
	if (t < ray->t_min || t > ray->t_max || t >= hit->t)
		return (false);
	intersection = ft_vect_add(ray->origin, ft_vect_mul_all(ray->direction, t));
	vec_to_center = ft_vect_sub(intersection, cap_center);
	dist_squared = ft_vect_dot(vec_to_center, vec_to_center)
		- pow(ft_vect_dot(vec_to_center, cap_normal), 2);
	if (dist_squared > radius * radius)
		return (false);
	hit->t = t;
	hit->point = intersection;
	hit->normal = cap_normal;
	hit->object = cylinder;
	hit->front_face = ft_vect_dot(ray->direction, cap_normal) < 0;
	if (!hit->front_face)
		hit->normal = ft_vect_mul_all(cap_normal, -1);
	u = (vec_to_center.x / radius + 1) * 0.5;
	v = (vec_to_center.z / radius + 1) * 0.5;
	hit->u = u;
	hit->v = v;
	return (true);
}

/*
 * Calculate UV coordinates on the cylinder for texture mapping
 */
void	ft_calculate_cylinder_uv(t_hit **hit, t_obj_data *cylinder,
		double height_proj)
{
	t_vect	axis;
	t_vect	vec_to_hit;
	t_vect	ref;
	t_vect	perp;
	t_vect	binormal;
	t_vect	projected;
	double	theta;

	axis = cylinder->norm_dir;
	vec_to_hit = ft_vect_sub((*hit)->point, cylinder->cord);
	if (fabs(axis.y) < 0.999)
		ref = (t_vect){0, 1, 0};
	else
		ref = (t_vect){1, 0, 0};
	perp = ft_vect_norm(ft_vect_cross(axis, ref));
	binormal = ft_vect_cross(axis, perp);
	projected = ft_vect_sub(vec_to_hit, ft_vect_mul_all(axis, height_proj));
	theta = atan2(ft_vect_dot(binormal, ft_vect_norm(projected)),
			ft_vect_dot(perp, ft_vect_norm(projected)));
	(*hit)->u = (theta + M_PI) / (2 * M_PI);
	(*hit)->v = (height_proj + cylinder->props.t_cylinder.half_height) / (2
			* cylinder->props.t_cylinder.half_height);
}

/*
 * Main cylinder intersection function that checks all parts of the cylinder
 */
bool	ft_intersect_cylinder(t_ray *ray, t_obj_data *cylinder, t_hit *hit)
{
	t_quadratic	quad;
	bool		hit_anything;

	hit_anything = false;
	t_hit temp_hit = *hit; // Store current closest hit
	// Check intersection with cylinder side
	if (ft_intersect_cylinder_side(ray, cylinder, &quad, &temp_hit))
	{
		*hit = temp_hit;
		hit_anything = true;
	}
	// Check intersection with top cap
	if (ft_intersect_cylinder_cap(ray, cylinder, &temp_hit, true))
	{
		*hit = temp_hit;
		hit_anything = true;
	}
	// Check intersection with bottom cap
	if (ft_intersect_cylinder_cap(ray, cylinder, &temp_hit, false))
	{
		*hit = temp_hit;
		hit_anything = true;
	}
	return (hit_anything);
}

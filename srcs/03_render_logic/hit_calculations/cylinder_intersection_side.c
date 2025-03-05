/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection_side.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:35:16 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 10:43:02 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Calculate UV coordinates on the cylinder for texture mapping
 */
static void	ft_calculate_cylinder_uv(t_hit **hit, t_obj_data *cylinder,
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
 * Set up the quadratic equation coefficients for cylinder side intersection
 * Returns false if ray is parallel to cylinder axis
 */
static bool	ft_cylinder_side_setup_quadratic(t_ray *ray, t_obj_data *cylinder,
		t_quadratic *quad)
{
	t_vect	axis;
	double	radius;
	t_vect	oc;
	t_vect	ray_cross_axis;
	t_vect	oc_cross_axis;

	axis = cylinder->norm_dir;
	radius = cylinder->props.t_cylinder.radius;
	oc = ft_vect_sub(ray->origin, cylinder->cord);
	ray_cross_axis = ft_vect_cross(ray->direction, axis);
	oc_cross_axis = ft_vect_cross(oc, axis);
	quad->a = ft_vect_dot(ray_cross_axis, ray_cross_axis);
	if (fabs(quad->a) < EPSILON)
		return (false);
	quad->b = 2 * ft_vect_dot(ray_cross_axis, oc_cross_axis);
	quad->c = ft_vect_dot(oc_cross_axis, oc_cross_axis) - radius * radius;
	quad->discriminant = quad->b * quad->b - 4 * quad->a * quad->c;
	if (quad->discriminant >= 0)
	{
		quad->t1 = (-quad->b - sqrt(quad->discriminant)) / (2 * quad->a);
		quad->t2 = (-quad->b + sqrt(quad->discriminant)) / (2 * quad->a);
		return (true);
	}
	return (false);
}

/*
 * Check if the intersection point is within the cylinder's height
 */
static bool	ft_is_within_cylinder_height(t_vect point, t_obj_data *cylinder,
		double *height_proj)
{
	t_vect	axis;
	t_vect	vec_to_center;

	axis = cylinder->norm_dir;
	vec_to_center = ft_vect_sub(point, cylinder->cord);
	*height_proj = ft_vect_dot(vec_to_center, axis);
	return (fabs(*height_proj) <= cylinder->props.t_cylinder.half_height);
}

/*
 * Calculate the normal vector at the hit point on cylinder side
 */
static t_vect	ft_cylinder_side_normal(t_vect hit_point, t_obj_data *cylinder,
		double height_proj)
{
	t_vect	axis;
	t_vect	axis_point;
	t_vect	center_to_hit;

	axis = cylinder->norm_dir;
	axis_point = ft_vect_add(cylinder->cord, ft_vect_mul_all(axis,
				height_proj));
	center_to_hit = ft_vect_sub(hit_point, axis_point);
	return (ft_vect_norm(center_to_hit));
}

/*
 * Main function for cylinder side intersection
 */
bool	ft_intersect_cylinder_side(t_ray *ray, t_obj_data *cylinder,
		t_quadratic *quad, t_hit *hit)
{
	double	t;
	double	height_proj;
	t_vect	intersection;

	if (!ft_cylinder_side_setup_quadratic(ray, cylinder, quad))
		return (false);
	if (!ft_quadratic_find_closest_t(quad, ray, hit, &t))
		return (false);
	intersection = ft_vect_add(ray->origin, ft_vect_mul_all(ray->direction, t));
	if (!ft_is_within_cylinder_height(intersection, cylinder, &height_proj))
		return (false);
	hit->t = t;
	hit->point = intersection;
	hit->normal = ft_cylinder_side_normal(hit->point, cylinder, height_proj);
	hit->object = cylinder;
	hit->front_face = ft_vect_dot(ray->direction, hit->normal) < 0;
	if (!hit->front_face)
		hit->normal = ft_vect_mul_all(hit->normal, -1);
	ft_calculate_cylinder_uv(hit, cylinder, height_proj);
	return (true);
}

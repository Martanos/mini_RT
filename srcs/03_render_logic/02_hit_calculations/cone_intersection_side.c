/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection_side.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:45:37 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 14:48:37 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Check if intersection point is within the cone's height
 */
static bool	ft_is_within_cone_height(t_vect point, t_obj_data *cone,
		double *height_proj)
{
	t_vect	axis;
	t_vect	vec_to_apex;

	axis = cone->norm_dir;
	vec_to_apex = ft_vect_sub(point, cone->props.t_cone.apex);
	return (*height_proj >= 0 && *height_proj <= cone->props.t_cone.height);
}

/*
 * Calculate UV coordinates on the cone for texture mapping
 */
static void	ft_calculate_cone_uv(t_hit **hit, t_obj_data *cone,
		double height_proj)
{
	t_vect	axis_point;
	t_vect	ref;
	t_vect	perp;
	t_vect	binormal;
	t_vect	projected;
	double	cos_theta;
	double	sin_theta;
	double	theta;

	axis_point = ft_vect_add(cone->props.t_cone.apex,
			ft_vect_mul_all(cone->norm_dir, height_proj));
	if (fabs(cone->norm_dir.y) < 0.999)
		ref = (t_vect){0, 1, 0};
	else
		ref = (t_vect){1, 0, 0};
	perp = ft_vect_norm(ft_vect_cross(cone->norm_dir, ref));
	binormal = ft_vect_cross(cone->norm_dir, perp);
	projected = ft_vect_sub((*hit)->point, axis_point);
	cos_theta = ft_vect_dot(perp, ft_vect_norm(projected));
	sin_theta = ft_vect_dot(binormal, ft_vect_norm(projected));
	theta = atan2(sin_theta, cos_theta);
	(*hit)->u = (theta + M_PI) / (2 * M_PI);
	(*hit)->v = height_proj / cone->props.t_cone.height;
}

/*
 * Set up the quadratic equation coefficients for cone side intersection
 * Returns false if there's no possible intersection
 */
static bool	ft_cone_side_setup_quadratic(t_ray **ray, t_obj_data *cone,
		t_quadratic *quad)
{
	t_vect	axis;
	double	cos_apex;
	double	cos2;
	t_vect	oc;
	double	ray_dot_axis;
	double	oc_dot_axis;

	axis = cone->norm_dir;
	cos_apex = cone->props.t_cone.cos_apex;
	cos2 = cos_apex * cos_apex;
	oc = ft_vect_sub((*ray)->origin, cone->props.t_cone.apex);
	ray_dot_axis = ft_vect_dot((*ray)->direction, axis);
	oc_dot_axis = ft_vect_dot(oc, axis);
	quad->a = ray_dot_axis * ray_dot_axis - cos2;
	quad->b = 2.0 * (ray_dot_axis * oc_dot_axis - ft_vect_dot((*ray)->direction,
				oc) * cos2);
	quad->c = oc_dot_axis * oc_dot_axis - ft_vect_dot(oc, oc) * cos2;
	quad->discriminant = quad->b * quad->b - 4.0 * quad->a * quad->c;
	if (quad->discriminant < 0)
		return (false);
	quad->t1 = (-quad->b - sqrt(quad->discriminant)) / (2.0 * quad->a);
	quad->t2 = (-quad->b + sqrt(quad->discriminant)) / (2.0 * quad->a);
	return (true);
}

/*
 * Calculate the normal vector at the hit point on cone side
 */
static t_vect	ft_cone_side_normal(t_vect hit_point, t_obj_data *cone,
		double height_proj)
{
	t_vect	axis;
	double	slope;
	t_vect	axis_point;
	t_vect	perpendicular;
	t_vect	normal;

	axis = cone->norm_dir;
	slope = cone->props.t_cone.slope;
	axis_point = ft_vect_add(cone->props.t_cone.apex, ft_vect_mul_all(axis,
				height_proj));
	perpendicular = ft_vect_sub(hit_point, axis_point);
	normal = ft_vect_add(perpendicular, ft_vect_mul_all(axis, -height_proj
				* slope));
	return (ft_vect_norm(normal));
}

/*
 * Calculate ray intersection with the side of a cone
 * Returns true if a valid intersection is found
 */
bool	ft_intersect_cone_side(t_ray **ray, t_obj_data *cone, t_hit **hit)
{
	double		t;
	double		height_proj;
	t_vect		intersection;
	t_quadratic	quad;

	quad = (t_quadratic){0};
	if (!ft_cone_side_setup_quadratic(ray, cone, &quad))
		return (false);
	if (!ft_quadratic_find_closest_t(ray, hit, &quad, &t))
		return (false);
	intersection = ft_vect_add((*ray)->origin,
			ft_vect_mul_all((*ray)->direction, t));
	if (!ft_is_within_cone_height(intersection, cone, &height_proj))
		return (false);
	(*hit)->t = t;
	(*hit)->point = intersection;
	(*hit)->normal = ft_cone_side_normal(intersection, cone, height_proj);
	(*hit)->object = cone;
	(*hit)->front_face = ft_vect_dot((*ray)->direction, (*hit)->normal) < 0;
	if (!(*hit)->front_face)
		(*hit)->normal = ft_vect_mul_all((*hit)->normal, -1);
	ft_calculate_cone_uv(hit, cone, height_proj);
	return (true);
}

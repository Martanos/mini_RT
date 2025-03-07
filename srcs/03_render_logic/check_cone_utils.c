/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cone_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:05:00 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/07 18:08:45 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

/**
 * @brief Checks if a ray-cone intersection point lies within the cone's height
 * @param ray The ray to check intersection with
 * @param t The parameter value at which the ray intersects the cone
 * @param cone Pointer to the cone object being checked
 * @return The parameter t if intersection is within bounds, -1.0 otherwise
 */
double	check_height(t_ray ray, double t, t_cone *cone)
{
	t_vect	intersection;
	t_vect	v;
	double	height;
	t_vect	normalized_normal;

	intersection = get_cone_intersection_point(ray, t);
	v = ft_vect_sub(intersection, cone->cord);
	normalized_normal = ft_vect_norm(cone->norm);
	height = ft_vect_dot(v, normalized_normal);
	if (height >= 0 && height <= cone->height)
		return (t);
	return (-1.0);
}

/**
 * @brief Gets the intersection point for a ray at parameter t
 * @param ray The ray to calculate intersection for
 * @param t The parameter value at which the ray intersects
 * @return The intersection point in 3D space
 */
t_vect	get_cone_intersection_point(t_ray ray, double t)
{
	return (ft_vect_add(ray.origin, ft_vect_mul_all(ray.direction, t)));
}

/**
 * @brief Calculates the normal vector at a point on the cone
 * @param rec Hit record to update with normal information
 * @param ray The ray that hit the cone
 * @param cone The cone that was hit
 * @param axis_point The point on the cone's axis
 */
void	get_cone_normal(t_hit_record *rec, t_ray ray, t_cone *cone,
	t_vect axis_point)
{
	t_vect	radial;
	t_vect	outward_normal;
	double	radius_at_height;
	t_vect	expected_point;

	radius_at_height = get_radius_at_height(cone,
			get_cone_height(rec->point, cone));
	radial = get_radial_direction(rec->point, axis_point);
	expected_point = get_expected_point(axis_point, radial, radius_at_height);
	outward_normal = ft_vect_norm(ft_vect_sub(rec->point, expected_point));
	set_face_normal(rec, &ray, &outward_normal);
}

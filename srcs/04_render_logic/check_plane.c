/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:40:56 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/09 18:33:16 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

/**
 * @brief Checks if hit point is within plane's radius
 * @param ray The ray to check intersection with
 * @param plane The plane to check intersection with
 * @param t Distance to intersection point
 * @return True if hit point is within radius, false otherwise
 */
static int	is_within_radius(t_ray ray, t_plane *plane, double t)
{
	t_vect	hit_point;
	t_vect	to_center;
	double	distance_squared;

	if (plane->radius <= 0)
		return (1);
	hit_point = ft_vect_add(ray.origin,
			ft_vect_mul_all(ray.direction, t));
	to_center = ft_vect_sub(hit_point, plane->cord);
	distance_squared = ft_vect_dot(to_center, to_center);
	return (distance_squared <= plane->radius * plane->radius);
}

/**
 * @brief Checks if a ray intersects with a plane
 * @param ray The ray to check intersection with
 * @param plane The plane to check intersection with
 * @return Distance to intersection point, or -1.0 if no intersection
 */
double	check_plane_collision(t_ray ray, t_plane *plane)
{
	double	denom;
	double	t;
	t_vect	p0l0;

	denom = ft_vect_dot(plane->norm, ray.direction);
	if (fabs(denom) <= 1e-6)
		return (-1.0);
	p0l0 = ft_vect_sub(plane->cord, ray.origin);
	t = ft_vect_dot(p0l0, plane->norm) / denom;
	if (t < 0)
		return (-1.0);
	if (!is_within_radius(ray, plane, t))
		return (-1.0);
	return (t);
}

/**
 * @brief Finds the closest plane that intersects with the given ray
 * @param ray The ray to check intersections with
 * @param master The master structure containing plane list
 * @return t_plane_collision struct containing closest plane and distance
 */
t_plane_collision	find_closest_plane(t_ray ray, t_master *master)
{
	t_plane_collision	result;
	t_plane				*plane;
	double				t;

	result.closest_t = INFINITY;
	result.closest_plane = NULL;
	plane = master->plane_head;
	while (plane)
	{
		t = check_plane_collision(ray, plane);
		if (t > 0.0 && t < result.closest_t)
		{
			result.closest_t = t;
			result.closest_plane = plane;
		}
		plane = plane->next;
	}
	return (result);
}

/**
 * @brief Calculates intersection point and surface normal for a plane hit
 * @param ray The ray that hit the plane
 * @param collision The plane collision data
 * @param[out] rec Hit record to update with intersection details
 */
void	calculate_plane_hit(t_ray ray, t_plane_collision collision,
	t_hit_record *rec)
{
	rec->t = collision.closest_t;
	rec->point = ft_vect_add(ray.origin,
			ft_vect_mul_all(ray.direction, collision.closest_t));
	rec->normal = collision.closest_plane->norm;
	if (ft_vect_dot(ray.direction, rec->normal) > 0)
		rec->normal = ft_vect_mul_all(rec->normal, -1);
}

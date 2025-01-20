/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:07:50 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/13 14:00:03 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "plane.h"

double check_capped_plane_collision(t_ray ray, t_capped_plane plane)
{
	double	denom;
	t_vect	p0l0;
	double	t;
	t_vect	intersection_point;

	t_vect normal = vect_normalize(plane.normal);  // Ensure normal is normalized
	denom = vect_dot(normal, ray.direction);
	if (fabs(denom) < 1e-6)  // Ray is parallel to plane
		return (-1.0);

	p0l0 = vect_sub(plane.position, ray.origin);
	t = vect_dot(p0l0, normal) / denom;

	if (t < 0.0)  // Plane is behind ray
		return (-1.0);

	// Check if intersection point is within radius
	intersection_point = vect_add(ray.origin, vect_multiply(ray.direction, t));
	t_vect to_intersection = vect_sub(intersection_point, plane.position);
	// Project the vector onto the plane by removing its component along the normal
	double proj_length = vect_dot(to_intersection, vect_normalize(normal));
	t_vect projected = vect_sub(to_intersection, vect_multiply(vect_normalize(normal), proj_length));
	// Get the radial distance in the plane
	double radial_distance = vect_magnitude(projected);
	if (radial_distance > plane.radius)
		return (-1.0);

	return (t);
}

double	check_plane_collision(t_ray ray, t_plane_obj *plane)
{
	double	denom;
	t_vect	p0l0;
	double	t;

	t_vect normal = vect_normalize(plane->plane_normal);  // Ensure normal is normalized
	denom = vect_dot(normal, ray.direction);
	if (fabs(denom) < 1e-6)  // Ray is parallel to plane
		return (-1.0);

	p0l0 = vect_sub(plane->plane_pos, ray.origin);
	t = vect_dot(p0l0, normal) / denom;

	if (t < 0.0)  // Plane is behind ray
		return (-1.0);
	return (t);
}

t_plane_collision	find_closest_plane(t_ray ray, t_data *mlx_data)
{
	double			t;
	t_plane_collision result;
	t_plane_obj		*plane;
	int				i;

	i = 0;
	result.closest_t = INFINITY;
	result.closest_plane = NULL;
	while (mlx_data->instruction_set->plane_obj_list[i])
	{
		plane = mlx_data->instruction_set->plane_obj_list[i];
		t = check_plane_collision(ray, plane);
		if (t > 0.0 && t < result.closest_t)
		{
			result.closest_t = t;
			result.closest_plane = plane;
		}
		i++;
	}
	return (result);
}

void	calculate_plane_hit(t_ray ray, t_plane_collision collision, t_hit_record *rec)
{
	rec->t = collision.closest_t;
	rec->point = vect_add(ray.origin, vect_multiply(ray.direction, collision.closest_t));
	rec->normal = vect_normalize(collision.closest_plane->plane_normal);  // Ensure normal is normalized
}

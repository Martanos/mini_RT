/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:40:56 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/03 15:06:10 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "plane.h"

double	check_plane_collision(t_ray ray, t_plane *plane)
{
	double	denom;
	double	t;
	t_vect	p0l0;
	t_vect	hit_point;
	t_vect	to_center;
	double	distance_squared;

	denom = vect_dot(plane->norm, ray.direction);
	if (fabs(denom) > 1e-6)
	{
		p0l0 = vect_sub(plane->cord, ray.origin);
		t = vect_dot(p0l0, plane->norm) / denom;
		if (t >= 0)
		{
			// If plane has a radius, check if hit point is within radius
			if (plane->radius > 0)
			{
				hit_point = vect_add(ray.origin, vect_multiply(ray.direction, t));
				to_center = vect_sub(hit_point, plane->cord);
				distance_squared = vect_dot(to_center, to_center);
				if (distance_squared <= plane->radius * plane->radius)
					return (t);
				return (-1.0);
			}
			return (t);
		}
	}
	return (-1.0);
}

t_plane_collision	find_closest_plane(t_ray ray, t_data *mlx_data, t_master *master)
{
	double			t;
	t_plane_collision result;
	t_plane			*plane;

	(void)mlx_data;
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

void	calculate_plane_hit(t_ray ray, t_plane_collision collision, t_hit_record *rec)
{
	rec->t = collision.closest_t;
	rec->point = vect_add(ray.origin, vect_multiply(ray.direction, collision.closest_t));
	rec->normal = collision.closest_plane->norm;
}

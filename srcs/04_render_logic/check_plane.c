/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:40:56 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/04 16:23:33 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "libvect.h"

double	check_plane_collision(t_ray ray, t_plane *plane)
{
	double	denom = ft_vect_dot(plane->norm, ray.direction);
	if (fabs(denom) > 1e-6)
	{
		t_vect p0l0 = ft_vect_sub(plane->cord, ray.origin);
		double t = ft_vect_dot(p0l0, plane->norm) / denom;
		if (t >= 0)
		{
			if (plane->radius > 0)
			{
				t_vect hit_point = ft_vect_add(ray.origin, ft_vect_mul_all(ray.direction, t));
				t_vect to_center = ft_vect_sub(hit_point, plane->cord);
				double distance_squared = ft_vect_dot(to_center, to_center);
				if (distance_squared <= plane->radius * plane->radius)
					return (t);
				return (-1.0);
			}
			return (t);
		}
	}
	return (-1.0);
}

t_plane_collision	find_closest_plane(t_ray ray, t_master *master)
{
	double			t;
	t_plane_collision result;
	t_plane			*plane;

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
